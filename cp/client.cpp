#include "shared_memory.hpp"
#include "client_utils.hpp"

int main() {
    sem_t* generalSem = sem_open(generalSemName, O_RDWR | O_CREAT, 0777);
	int generalState; //состояние семафора

    std::string login;

    while(true){
        sem_getvalue(generalSem, &generalState);
        usleep(20000);
        if(generalState == 1){ // семафор свободен
            std::cout << "Введите логин: " ; 
            std::cin >> login;
            giveToMmap(login, clientServerName, generalSem, &generalState, 1); 
            setSemaphore(generalSem, &generalState, 0); // Устанавливаем семафор в заблокированное состояние (0)
            usleep(25000);
        } else if(generalState == 2){ // семафор занят
            std::string verificate = getFromMmap(serverClientName, 1);
            std::cout << verificate << std::endl;
            setSemaphore(generalSem, &generalState, 1); // Устанавливаем семафор в разрешенное состояние (1)
            break; 
        }
    }
    sem_t* startSem = OpenSemaphore(startSemName, 0);
    std::vector<std::string> ships; 
    std::string str(10, '0'); 
    std::vector<std::string> enemyShips(10, str); 

    giveShipCoord(login, ships);
    std::map<int, int> shipsCount;
    shipsCount[1] = 4; // Устанавливаем количество кораблей типа 1 (четырехпалубных) в 4
    shipsCount[2] = 3; // Устанавливаем количество кораблей типа 2 (трехпалубных) в 3
    shipsCount[3] = 2; // Устанавливаем количество кораблей типа 3 (двухпалубных) в 2
    shipsCount[4] = 1; // Устанавливаем количество кораблей типа 4 (однопалубных) в 1

    startGame(login, startSem, ships, enemyShips);
}