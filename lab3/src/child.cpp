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

    int source_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0);
    int response_fd = shm_open(RESPONSE_MEMORY_NAME, O_RDWR, 0);

    if (source_fd == -1 || response_fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    char* shared_memory_ptr = (char*)mmap(nullptr, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, source_fd, 0);
    char* response_memory_ptr = (char*)mmap(nullptr, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, response_fd, 0);

    sem_t* semaphore = sem_open(SEMAPHORE_NAME, 0);
    sem_t* response_semaphore = sem_open(RESPONSE_SEMAPHORE_NAME, 0);
    sem_wait(semaphore);

    std::string_view str(shared_memory_ptr);
    if (StartsWithCapital(str)) {
        out << str << std::endl;
    } else {
        strcpy(response_memory_ptr, "ERROR");
    }

    sem_post(response_semaphore);
    sem_close(semaphore);
    sem_close(response_semaphore);
    shm_unlink(SHARED_MEMORY_NAME);
    shm_unlink(RESPONSE_MEMORY_NAME);

    return 0;
}
