#include "server_utils.hpp"

std::vector<int> parseCoordinates(std::string input) {
    std::string str;
    for (size_t i = 2; i < input.size(); ++i) {
        str += input[i];
    }
    std::istringstream iss(str);
    std::vector<int> numbers;
    int number;
    while (iss >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

//расстановка кораблей
void arrangementShips(std::vector<std::vector<std::string>> &twoMatrix, std::vector<int> coordinates, int player) {
    coordinates[0]--;
    coordinates[1]--;
    coordinates[2]--;
    coordinates[3]--;
    if (coordinates[0] == coordinates[2]) {
        while (coordinates[1] <= coordinates[3]) {
            twoMatrix[player][coordinates[0]][coordinates[1]] = '1';
            ++coordinates[1];
            if (coordinates[1] > 9) {
                break;
            }
        }
    } else {
        while (coordinates[0] <= coordinates[2]) {
            twoMatrix[player][coordinates[0]][coordinates[3]] = '1';
            ++coordinates[0];
            if (coordinates[0] > 9) {
                break;
            }
        }
    }
}

void shipLocation(std::vector<std::string> players, std::vector<std::vector<std::string>>& twoMatrix, std::map<std::string, int> statistic) {
    // Создание семафоров для каждого игрока
    std::vector<const char*> semName(2);
    semName[0] = (players[0] + "_sem").c_str();
    semName[1] = (players[1] + "_sem").c_str();
    std::vector<sem_t*> semaphores(2);
    semaphores[0] = OpenSemaphore(semName[0], 1);
    semaphores[1] = OpenSemaphore(semName[1], 1);

    std::vector<std::string> mmapClientServer(2);
    mmapClientServer[0] = players[0] + "_server";
    mmapClientServer[1] = players[1] + "_server";

    std::vector<std::string> mmapServerClient(2);
    mmapServerClient[0] = "server_" + players[0];
    mmapServerClient[1] = "server_" + players[1];

    std::vector<int> states(2, 1); //состояние семафоров игроков
    std::vector<int> shipsCount(2, 0); // количество кораблей каждого игрока

    bool flag = 1;

    // начальное расположение кораблей
    while(flag) {
        for(int playerIndex = 0; playerIndex < 2; playerIndex++) {
            sem_getvalue(semaphores[playerIndex], &states[playerIndex]);

            if(shipsCount[0] == 10 && shipsCount[1] == 10) {
                flag = 0;
                break;
            }
            if(states[playerIndex] == 0) {
                std::string info = getFromMmap(mmapClientServer[playerIndex], 1);
                if(info == "-1") {
                    int num = statistic[players[playerIndex]];
                    giveToMmap(std::to_string(num), mmapServerClient[playerIndex], semaphores[playerIndex], &states[playerIndex], 1);
                } else {
                    std::vector<int> coords = parseCoordinates(info);
                    std::cout << players[playerIndex] << ": " << info << std::endl;
                    arrangementShips(twoMatrix, coords, playerIndex);
                    ++shipsCount[playerIndex];
                    giveToMmap("OK!", mmapServerClient[playerIndex], semaphores[playerIndex], &states[playerIndex], 1);
                }
                //блокировка семафора
                setSemaphore(semaphores[playerIndex], &states[playerIndex], 2);
                usleep(25000);
            } else {
                usleep(25000);
            }
        }
    }
    // Сброс счетчиков кораблей для новой фазы игры
    shipsCount[0] = 0;
    shipsCount[1] = 0;
    flag = 1;
    // Цикл для передачи координат выстрелов и получения результатов от клиентов
    while (flag) {
        for (int playerIndex = 0; playerIndex < 2; ++playerIndex) {
            // Получение текущего состояния семафора
            sem_getvalue(semaphores[playerIndex], &states[playerIndex]);

            if (shipsCount[0] == 10 && shipsCount[1] == 10) {
                flag = 0;
                break;
            }
            if (states[playerIndex] == 1) {
                // Отправка координат выстрела клиенту через разделяемую память
                giveToMmap(twoMatrix[playerIndex][shipsCount[playerIndex]].c_str(), mmapServerClient[playerIndex], semaphores[playerIndex], &states[playerIndex], 1);
                ++shipsCount[playerIndex];
                // Разблокировка семафора
                setSemaphore(semaphores[playerIndex], &states[playerIndex], 0);
                usleep(25000);
            }
        }
    }
}

std::string battleInfo(std::vector<std::string>& matrix, int x, int y) {
    --x;
    --y;
    std::string result;
    if(matrix[x][y] == '0') {
        matrix[x][y] = '3';
        result = "Мимо";
    }
    if(matrix[x][y] == '1') {
        matrix[x][y] = '2';
        result = "Ранил";
    } else {
        result = "Мимо";
    }
    return result;
}

void getCoordSer(std::string str, int* x, int* y) {
    std::string str1;
    size_t i = 0;
    for(; i < str.size(); ++i) {
        if(str[i] == ' ') {
            break;
        }
    }
    ++i;
    for(; i < str.size(); ++i) {
        str1 += str[i];
    }
    std::istringstream iss(str1);
    std::vector<int> numbers;

    int number;
    while(iss >> number) {
        numbers.push_back(number);
    }

    *x = numbers[0];
    *y = numbers[1];
}

void startGame(std::vector<std::vector<std::string>>& twoMatrix, std::vector<std::string> players, sem_t* startSemaphore, std::map<std::string, int>& statistic) {
    int nowMove = 0; // текущий ход (0 - первый игрок, 1 - второй игрок)
    int state = 0; // состояние семафора
    std::vector<std::string> mmapClientServer(2);
    
    mmapClientServer[0] = players[0] + "_server_start";
    mmapClientServer[1] = players[1] + "_server_start";
    std::vector<std::string> mmapServerClient(2); 

    mmapServerClient[0] = "server_" + players[0] + "_start";
    mmapServerClient[1] = "server_" + players[1] + "_start";
    sem_getvalue(startSemaphore, &state); // получение текущего значения семафора
    bool flag = 1;
    std::vector<int> count(2, 0); // попадания для каждого игрока
    std::string win; 
    while (flag) { 
        sem_getvalue(startSemaphore, &state); // Получение текущего значения семафора

        if (state == 0) { 
            std::string info = players[nowMove]; // Получение информации о текущем игроке
            
            giveToMmap(info, mmapServerClient[0], startSemaphore, &state, 1);
            giveToMmap(info, mmapServerClient[1], startSemaphore, &state, 1);
            setSemaphore(startSemaphore, &state, 1); // Установка семафора в значение 1
            usleep(25000); 
        } else if (state == 2) { 
            std::string info, info1; 
            
            if (nowMove == 0) {
                info = getFromMmap(mmapClientServer[0],  1);
                std::cout << info << std::endl; 
            }
            if (nowMove == 1) {
                info1 = getFromMmap(mmapClientServer[1],  1);
                std::cout << info1 << std::endl; 
            }
            std::string login; 
            int x, y; // координаты выстрела
            
            if (nowMove == 0) {
                login = players[0]; 
                getCoordSer(info, &x, &y); 
                
                std::string answer = battleInfo(twoMatrix[1], x, y);
                if (answer == "Ранил") {
                    ++count[1]; 
                }
                login += " " + answer + " " + std::to_string(x) + " " + std::to_string(y);
            }
            
            if (nowMove == 1) {
                login = players[1]; 
                getCoordSer(info1, &x, &y); 
                
                std::string answer = battleInfo(twoMatrix[0], x, y);
                if (answer == "Ранил") {
                    ++count[0]; 
                }
                login += " " + answer + " " + std::to_string(x) + " " + std::to_string(y); 
            }
            // проверка условия победы первого игрока
            if (count[1] == 20) {
                win = players[0];
                ++statistic[win]; 
                std::cout << "Победитель: " << win << std::endl; 
                usleep(25000);
                
                giveToMmap(win, mmapServerClient[0], startSemaphore, &state, 1);
                giveToMmap(win, mmapServerClient[1], startSemaphore, &state, 1);
                setSemaphore(startSemaphore, &state, 6);
                usleep(25000);
                flag = 0; 
            }
            // проверка условия победы второго игрока
            if (count[0] == 20) {
                win = players[1]; 
                ++statistic[win];
                std::cout << "Победитель: " << win << std::endl; 
                
                giveToMmap(win, mmapServerClient[0], startSemaphore, &state, 1);
                giveToMmap(win, mmapServerClient[1], startSemaphore, &state, 1);
                setSemaphore(startSemaphore, &state, 6);
                usleep(25000);
                flag = 0; 
            }
            // продолжение игры
            if (flag == 1) {
                giveToMmap(login, mmapServerClient[0], startSemaphore, &state, 1);
                giveToMmap(login, mmapServerClient[1], startSemaphore, &state, 1);
                nowMove = nowMove ^ 1;
                setSemaphore(startSemaphore, &state, 3); 
                usleep(25000);
            }
        } else {
            usleep(50000);
        }
    }
    usleep(25000);
}
