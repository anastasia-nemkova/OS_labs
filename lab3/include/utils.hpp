#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <cstring>
#include <cctype>
#include <vector>

pid_t CreateChildProcess();
bool StartsWithCapital(const std::string& str);
int OpenSharedMemory(const char* SHARED_MEMORY_NAME, int SIZE);
char* MapSharedMemory(int SIZE, int fd);
sem_t* OpenSemaphore(const char* SEMAPHORE_NAME);
