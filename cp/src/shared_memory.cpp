#include "shared_memory.hpp"

int OpenSharedMemory(const char* sharedMemoryName, int size) {
    int shared_memory_fd = shm_open(sharedMemoryName, O_CREAT | O_RDWR, 0777);
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

void giveToMmap(std::string input, std::string MmapName, sem_t * semaphore, int * state, bool close_file) {
    int size = input.size();
    int file = OpenSharedMemory(MmapName.c_str(), size);
    char* mapped = MapSharedMemory(size, file);
    memset(mapped, '\0', size);
    sprintf(mapped, "%s", input.c_str());
    if(sem_getvalue(semaphore, state) == -1) {
        perror("Failed to get semaphore value");
        exit(EXIT_FAILURE);
    }
    if(close_file) {
        if (munmap(mapped, size) == -1) {
            perror("Can't munmap shared memory object");
            exit(EXIT_FAILURE);
        }
        close(file);
    }
}
std::string getFromMmap(std::string MmapName, bool close_file) {
    int file = shm_open(MmapName.c_str(), O_CREAT | O_RDWR, 0777);
    struct stat stat_buffer;// хранение информации о файле
    
    if (fstat(file, &stat_buffer) == -1) {//получаем информацию о файле и сохраняем ее в stat_buffer
        return "Fail";
    }

    int size = stat_buffer.st_size;
    char* mapped = MapSharedMemory(size, file);
    std::string str(mapped, stat_buffer.st_size);//строка с данными из отображаемой памяти
    if (close_file) {
        if (munmap(mapped, size) == -1) {
            perror("Can't munmap shared memory object");
            exit(EXIT_FAILURE);
        }
        close(file);
    }

    return str;
}
sem_t* OpenSemaphore(const char* semaphoreName, int state) {
    sem_t* semaphore = sem_open(semaphoreName, O_CREAT | O_RDWR, 0777, state);
    if (semaphore == SEM_FAILED) {
        perror("Can't open semaphore");
        exit(-1);
    }
    return semaphore;
}

// уствнавливаем занчение семафора в value
void setSemaphore(sem_t *semaphore, int *state, int value) {
     while (++(*state) < value + 1) {
        sem_post(semaphore);
    }
    while (--(*state) > value) {
        sem_wait(semaphore);
    }
}
