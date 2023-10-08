#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void CreatePipe(int fd[2]);
pid_t CreateChildProcess();
bool StartsWithCapital(const std::string& str);
void ReadFromPipe2(int fd);
