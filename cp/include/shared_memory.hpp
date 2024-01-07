#pragma once

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <map>
#include <sys/types.h>
#include <vector>
#include <limits.h>
#include <semaphore.h>
#include <sstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <string_view>

constexpr const char* generalSemName = "/general_sem";
constexpr const char* startSemName = "/start_sem";
const std::string clientServerName = "/client_server";
const std::string serverClientName = "/server_client";

int OpenSharedMemory(const char* sharedMemoryName, int size);
char* MapSharedMemory(int size, int fd);
void giveToMmap(std::string input, std::string MmapName, sem_t * semaphore, int * state, bool close_file);
std::string getFromMmap(std::string MmapName, bool close_file);
sem_t* OpenSemaphore(const char* semaphoreName, int state);
void setSemaphore(sem_t *semaphore, int *state, int value);
