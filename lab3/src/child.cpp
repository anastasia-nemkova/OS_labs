#include "utils.hpp"

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        perror("Necessary arguments were not provided");
        exit(EXIT_FAILURE);
    }
    const char* SHARED_MEMORY_NAME = "shared_memory";
    const char* SEMAPHORE_NAME = "semaphore";
    const int SIZE = 1024;

    const char* fileName = argv[1];
    std::ofstream out(fileName);
    if(!out.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    int shared_memory_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0);
    char* shared_memory_ptr = (char*)mmap(nullptr, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
    sem_t* semaphore = sem_open(SEMAPHORE_NAME, 0);
    
    sem_wait(semaphore);
    std::string str(shared_memory_ptr);
    if (StartsWithCapital(str)) {
        out << str << std::endl;
    } else {
        strcpy(shared_memory_ptr, "ERROR");
    }

    sem_post(semaphore);
    sem_close(semaphore);
    exit(EXIT_FAILURE);;
}