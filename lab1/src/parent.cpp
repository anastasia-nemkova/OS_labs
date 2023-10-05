#include "parent.hpp"
#include "utils.hpp"

// fd[1] - запись
// fd[0] - чтение

void ParentRoutine(const char* pathToChild){
    std::string fileName;
    //std::cout << "Enter the file name: ";
    getline(std::cin, fileName);
   
    int fd_1[2];
    int fd_2[2];
    CreatePipe(fd_1); //pipe между родителем и дочерним
    CreatePipe(fd_2); //pipe между дочерним и родителем


    int pid = CreateChildProcess();// создаем дочерний процесс
   
    if (pid == 0) { // дочерний процесс
        close(fd_1[1]); //закрываем запись в pipe1
        close(fd_2[0]); //закрываем чтение из pipe2

        dup2(fd_1[0], STDIN_FILENO); // перенаправляем считанные с pipe1 данные на стандартный вывод
        dup2(fd_2[1], STDOUT_FILENO);

        if (execlp(pathToChild, pathToChild, fileName.c_str(), nullptr) == -1) { // запускаем child.cpp
            perror("Child start error");
            exit(EXIT_FAILURE);
        }

    } else { // родительский процесс


        close(fd_1[0]); //закрываем чтение из pipe1
        close(fd_2[1]); //закрываем запись в pipe2

        std::string str;
        //std::cout << "Enter strings:" << std::endl;
        while (std::getline(std::cin, str)) { //считываем строку с консоли и записываем в pipe1
            write(fd_1[1], str.c_str(), str.length());
            write(fd_1[1],"\n", 1);
        }
        close(fd_1[1]);

        ReadFromPipe2(fd_2[0]);
        close(fd_2[0]);

        wait(nullptr);
    }
}
