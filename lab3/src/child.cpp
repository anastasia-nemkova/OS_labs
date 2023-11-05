#include "utils.hpp"

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        perror("Necessary arguments were not provided");
        exit(EXIT_FAILURE);
    }
    const char* SHARED_MEMORY_NAME = "/shared_memory";
    const char* RESPONSE_MEMORY_NAME = "/response_memory";
    const char* SEMAPHORE_NAME = "/semaphore";
    const char* RESPONSE_SEMAPHORE_NAME = "/response_semaphore";
    const int SIZE = 1024;
    
    const char* fileName = argv[1];
    std::ofstream out(fileName, std::ios::app);
    if(!out.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    int shared_memory_fd = OpenSharedMemory(SHARED_MEMORY_NAME, SIZE);
    int response_fd = OpenSharedMemory(RESPONSE_MEMORY_NAME, SIZE);

    char* shared_memory_ptr = MapSharedMemory(SIZE, shared_memory_fd);
    char* response_memory_ptr = MapSharedMemory(SIZE, response_fd);;

    sem_t* semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 0); 
    sem_t* response_semaphore = sem_open(RESPONSE_SEMAPHORE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 0); 
    if (semaphore == SEM_FAILED || response_semaphore == SEM_FAILED) {
        perror("Error opening semaphores");
        exit(EXIT_FAILURE);
    }
    
    while (true) {
        sem_wait(semaphore);
        std::string_view str(shared_memory_ptr);

        if (str.empty()) {
            sem_post(response_semaphore);
            break;
        }
        
        if (StartsWithCapital(str)) {
            out << str << std::endl;
        } else {
            strcpy(response_memory_ptr, "ERROR");
        }
        
        sem_post(response_semaphore);
    }

    sem_close(semaphore);
    sem_close(response_semaphore);
    munmap(shared_memory_ptr, SIZE);
    munmap(response_memory_ptr, SIZE);
    sem_unlink(SEMAPHORE_NAME);
    sem_unlink(RESPONSE_SEMAPHORE_NAME);
    shm_unlink(SHARED_MEMORY_NAME);
    shm_unlink(RESPONSE_MEMORY_NAME);

    exit(EXIT_SUCCESS);
}
