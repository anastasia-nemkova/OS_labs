#include "parent.hpp"
#include "utils.hpp"


void ParentRoutine(const char* pathToChild){
    std::string fileName;
    getline(std::cin, fileName);

    const char* SHARED_MEMORY_NAME = "shared_memory";
    const char* SEMAPHORE_NAME = "semaphore";
    const int SIZE = 1024;

    int shared_memory_fd = OpenSharedMemory(SHARED_MEMORY_NAME, SIZE);
    char* shared_memory_ptr = MapSharedMemory(SIZE, shared_memory_fd);
    sem_t* semaphore = OpenSemaphore(SEMAPHORE_NAME);

    std::vector<std::string> lines;
    while (true) {
        std::string str;
        if (!std::getline(std::cin, str) || str.empty()) {
            break;
        }
        lines.push_back(str);
    }
    for (const std::string& line : lines) {
        sem_wait(semaphore);
        strcpy(shared_memory_ptr, line.c_str());
        sem_post(semaphore);

        pid_t pid = CreateChildProcess();

        if (pid == 0) {
            execlp(pathToChild, pathToChild, fileName.c_str(), nullptr);
            perror("Exec failed");
            exit(EXIT_FAILURE);
        } else {
            int status;
            wait(&status);

            sem_wait(semaphore);

            if (strcmp(shared_memory_ptr, "ERROR") == 0) {
                std::cerr << "Error: " << line << std::endl;
            }

            sem_post(semaphore);
        }
    }

    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);
    shm_unlink(SHARED_MEMORY_NAME);
}


