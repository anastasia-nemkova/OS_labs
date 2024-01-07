#pragma once

#include "shared_memory.hpp"

std::string getLogin(std::string str);
std::string getCoord(std::string str, int* x, int* y);
void battleInfo(std::vector<std::string>& matrix, int x, int y, std::string info);
void printMap(std::vector<std::string> matrix);
void printEmptyMap();
int convert(std::string letter);
void giveShipCoord(std::string login, std::vector<std::string>& ships);
void startGame(std::string login, sem_t* semaphore, std::vector<std::string>& ships, std::vector<std::string>& enemyShips);