#include "parent.hpp"
#include "utils.hpp"


void ParentRoutine(const char* pathToChild){
    std::string fileName;
    getline(std::cin, fileName);

    const char* SHARED_MEMORY_NAME = "/shared_memory";
    const char* RESPONSE_MEMORY_NAME = "/response_memory";
    const char* SEMAPHORE_NAME = "/semaphore";
    const char* RESPONSE_SEMAPHORE_NAME = "/response_semaphore";
    const int SIZE = 1024;

    int shared_memory_fd = OpenSharedMemory(SHARED_MEMORY_NAME, SIZE);
    int response_fd = OpenSharedMemory(RESPONSE_MEMORY_NAME, SIZE);
    char* shared_memory_ptr = MapSharedMemory(SIZE, shared_memory_fd);
    char* response_memory_ptr = MapSharedMemory(SIZE, response_fd);
    sem_t* semaphore = OpenSemaphore(SEMAPHORE_NAME);
    sem_t* response_semaphore = OpenSemaphore(RESPONSE_SEMAPHORE_NAME);

    pid_t pid = CreateChildProcess();

    if (pid == 0) {
        execlp(pathToChild, pathToChild, fileName.c_str(), nullptr);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        std::vector<std::string> lines;
        std::string str;
        while (std::getline(std::cin, str) && !str.empty()) {
            lines.push_back(str);
        }

        for (const std::string& line : lines) {
            sem_wait(semaphore);
            strcpy(shared_memory_ptr, line.c_str());
            sem_post(semaphore);

            sem_wait(response_semaphore);
            if (strcmp(response_memory_ptr, "ERROR") == 0) {
                std::cerr << "Error: " << line << std::endl;
            }
            sem_post(response_semaphore);
        }

        wait(nullptr); 
    }

    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);
    sem_close(response_semaphore);
    sem_unlink(RESPONSE_SEMAPHORE_NAME);
    shm_unlink(SHARED_MEMORY_NAME);
    shm_unlink(RESPONSE_MEMORY_NAME);
}