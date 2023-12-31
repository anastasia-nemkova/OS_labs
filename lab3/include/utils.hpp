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
#include <string_view>

constexpr const char* SHARED_MEMORY_NAME = "/shared_memory";
constexpr const char* RESPONSE_MEMORY_NAME = "/response_memory";
constexpr const char* SEMAPHORE_NAME = "/semaphore";
constexpr const char* RESPONSE_SEMAPHORE_NAME = "/response_semaphore";
constexpr int SIZE = 1024;

pid_t CreateChildProcess();
bool StartsWithCapital(const std::string_view str);
int OpenSharedMemory(const char* sharedMemoryName, int size);
char* MapSharedMemory(int size, int fd);
sem_t* OpenSemaphore(const char* semaphoreName);
