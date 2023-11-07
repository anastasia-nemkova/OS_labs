#include "utils.hpp"

pid_t CreateChildProcess() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating process");
        exit(EXIT_FAILURE);
    }
    return pid;
}

bool StartsWithCapital(const std::string_view str) {
    return !str.empty() && isupper(str[0]);
}

int OpenSharedMemory(const char* sharedMemoryName, int size) {
    int shared_memory_fd = shm_open(sharedMemoryName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shared_memory_fd == -1) {
        perror("Can't open shared memory object");
        exit(-1);
    }

    if (ftruncate(shared_memory_fd, size) == -1) {
        perror("Can't resize shared memory object");
        exit(-1);
    }

    return shared_memory_fd;
}

char* MapSharedMemory(int size, int fd) {
    char* shared_memory_ptr = (char*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory_ptr == MAP_FAILED) {
        perror("Can't mmap shared memory object");
        exit(-1);
    }
    return shared_memory_ptr;
}

sem_t* OpenSemaphore(const char* semaphoreName) {
    sem_t* semaphore = sem_open(semaphoreName, O_CREAT, S_IRUSR | S_IWUSR, 0);
    if (semaphore == SEM_FAILED) {
        perror("Can't open semaphore");
        exit(-1);
    }
    return semaphore;
}
