#pragma once

#include "shared_memory.hpp"

std::vector<int> parseCoordinates(std::string input);
void arrangementShips(std::vector<std::vector<std::string>> &twoMatrix, std::vector<int> coordinates, int player);
void shipLocation(std::vector<std::string> players, std::vector<std::vector<std::string>>& two_matrix, std::map<std::string, int> statistic);
std::string battleInfo(std::vector<std::string>& matrix, int x, int y);
void getCoordSer(std::string str, int* x, int* y);
void startGame(std::vector<std::vector<std::string>>& two_matrix, std::vector<std::string> players, sem_t* startSemaphore, std::map<std::string, int>& statistic);