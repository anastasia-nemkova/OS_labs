#include "utils.hpp"

void CreatePipe(int fd[2]) {
    if (pipe(fd) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
}

pid_t CreateChildProcess() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating process");
        exit(EXIT_FAILURE);
    }
    return pid;
}

bool StartsWithCapital(const std::string& str) {
    return !(str.empty()) && isupper(str[0]);
}

void ReadFromPipe2(int fd) {
    constexpr int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE] = "";
    ssize_t bytesRead;
   
    while ((bytesRead = read(fd, &buffer, BUFFER_SIZE)) > 0) {
        std::cout.write(buffer, bytesRead);
    }
   
    std::cout << std::endl;
   
    if (bytesRead == -1) {
        perror("Error reading from pipe2");
        exit(EXIT_FAILURE);
    }
}
