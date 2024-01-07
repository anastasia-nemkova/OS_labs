#include "client_utils.hpp"

std::string getLogin(std::string str) {
    std::string result;
    for(size_t i = 0; i < str.size(); ++i) {
        if(str[i] == ' '){
            break;
        }
        result += str[i];
    }
    return result;
}

std::string getCoord(std::string line, int* x, int* y){
    std::string str;
    std::string str1;
    size_t strIndex = 0;
    for(; strIndex < line.size(); ++strIndex) {
        if(line[strIndex] == ' ') {
            break;
        }
    }
    ++strIndex;
    for(; strIndex < line.size(); ++strIndex) {
        if(line[strIndex] == ' ') {
            break;
        }
        str += line[strIndex];
    }
    ++strIndex;
    for(; strIndex < line.size(); ++strIndex) {
        str1 += line[strIndex];
    }

    std::istringstream iss(str1);
    std::vector<int> numbers;

    int number;
    while(iss >> number) {
        numbers.push_back(number);
    }
    *x = numbers[0];
    *y = numbers[1];

    return str;
}

void battleInfo(std::vector<std::string>& matrix, int x, int y, std::string info){
    --x;
    --y;
    if(info=="Мимо"){
        matrix[x][y] = '3';
    }

    if(info=="Ранил"){
        matrix[x][y] = '2';
    }
}

void printMap(std::vector<std::string> matrix){
    std::cout << "    a b c d e f g h i j" << std::endl;
    std::cout << "    ———————————————————" << std::endl;
    int number = 1;
    for(int rowIndex = 0;rowIndex < 10; ++rowIndex) {
        if(number == 10) {
            std::cout << number <<" |";
        } else {
            std::cout << number << "  |";
        }
        for(int columnIndex = 0; columnIndex < 10; ++columnIndex) {
            if(matrix[columnIndex][rowIndex]=='3'){
                std::cout << "-" << " ";
            }
            if(matrix[columnIndex][rowIndex]=='2'){
                std::cout << "X" << " ";
            }
            if(matrix[columnIndex][rowIndex]=='1'){
                std::cout << "^" << " ";
            }
            if(matrix[columnIndex][rowIndex]=='0'){
                std::cout << "." << " ";
            }
        }
        std::cout << "|" << std::endl;
        ++number;
    }
	std::cout << "    ———————————————————" << std::endl;
}

void printEmptyMap() {
    std::cout << "    a b c d e f g h i j" << std::endl;
    std::cout << "    ———————————————————" << std::endl;
    int number = 1;
    for(int i = 0; i < 10; ++i) {
        if(number == 10) {
            std::cout << number <<" |";
        } else {
            std::cout << number << "  |";
        }
        for(int j = 0; j < 10; ++j) {
            std::cout << "." << " ";
        }
        std::cout << "|" << std::endl;
        ++number;
    }
    std::cout << "    ———————————————————" << std::endl;
}

int convert(std::string letter) {
    return letter[0] - 'a' + 1;
}

void giveShipCoord(std::string login, std::vector<std::string>& ships) {
    const char* semName = (login + "_sem").c_str();
    sem_unlink(semName);
    sem_t* semaphore = OpenSemaphore(semName, 1);
    int state = 1;// состояние семафора
    sem_getvalue(semaphore, &state);
    setSemaphore(semaphore, &state, 1);
    std::string clientServerName = login + "_server";
    std::string serverClientName = "server_" + login;

    std::cout << "Ваше поле" << std::endl;
    printEmptyMap();
    
    std::cout << "Введите размер и координаты корабля на поле" << std::endl;

    int shipCount = 0;

    while(true) {
        sem_getvalue(semaphore, &state);
        usleep(25000);

        // семафор свободен
        if(state == 1) {
            int shipSize, coordAx, coordAy, coordBx, coordBy;
            std::string coordA, coordB;
            std::cin >> shipSize;
            if(shipSize == -1) {
                giveToMmap(std::to_string(shipSize), clientServerName, semaphore, &state, 1);
                setSemaphore(semaphore, &state, 0);
                usleep(25000);
            } else {
                std::cin >> coordA >> coordB;
                if (coordA.size() == 3) {
                coordAy = 10;
                } else {
                    coordAy = coordA[1] - '0';
                }
                
                if (coordB.size() == 3) {
                    coordBy = 10;
                } else {
                    coordBy = coordB[1] - '0';
                }
                coordBx = convert(coordB.substr(0, 1)); // Конвертируем первый символ coordB в число
                coordAx = convert(coordA.substr(0, 1));

                std::string finalStr = std::to_string(shipSize) + " " +
                                    std::to_string(coordAx) + " " +
                                    std::to_string(coordAy) + " " +
                                    std::to_string(coordBx) + " " +
                                    std::to_string(coordBy) + " ";
                giveToMmap(finalStr, clientServerName, semaphore, &state, 1);
                setSemaphore(semaphore, &state, 0);
                usleep(25000);
            }
        } else if (state == 2) { // семафор занят сервером
            std::string info = getFromMmap(serverClientName, 1);
            if(info != "OK!") {
                std::cout << "Статистика" << info << std::endl;
                setSemaphore(semaphore, &state, 1);
                usleep(25000);
            } else {
                std::cout << info << std::endl;
                ++shipCount;
                setSemaphore(semaphore, &state, 1);
                usleep(25000);

                if(shipCount == 10) {
                    break;
                }
            }
        }
    }

    shipCount = 0;
    bool flag = 1;
    while(flag) {
        usleep(25000);
        sem_getvalue(semaphore, &state);

        if(state == 0) {
            std::string shipCoord = getFromMmap(serverClientName, 1);
            ships.push_back(shipCoord);
            ++shipCount;
            setSemaphore(semaphore, &state, 1);
            usleep(25000);

            if(shipCount == 10) {
                flag = 0;
            }
        }
    }
    printMap(ships);
}

void startGame(std::string login, sem_t* semaphore, std::vector<std::string>& ships, std::vector<std::string>& enemyShips) {
    int state = 0;
    sem_getvalue(semaphore, &state);

    std::string clientServerName = login + "_server_start";
    std::string serverClientName = "server_" + login + "_start";
    std::cout << "Игра началась" << std::endl;

    int count = 0; //попадания
    bool flag = 1;
    while(flag) {
        sem_getvalue(semaphore, &state);
        usleep(25000);

        // игрок должен совершить ход
        if(state == 1) {
            std::string info = getFromMmap(serverClientName, 1);
            if(login != info) {
                usleep(10000);
                continue;
            } else {
                std::string coords;
                std::cout << "Вы ходите" << std::endl;
                std::string crd;
                int x, y;
                std::cin >> crd;
                if (crd.size() == 3) {
                    y = 10;
                } else {
                    y = crd[1] - '0';
                }
                x = convert(crd.substr(0, 1));
                coords = " " + std::to_string(x) + " " + std::to_string(y);
                std::string giveInfo = login + coords;
                giveToMmap(giveInfo, clientServerName, semaphore, &state, 0);
                usleep(200000);
                setSemaphore(semaphore, &state, 2);
                usleep(25000);
            }
        } else if (state == 3) { // результаты хода
            std::string infoServer = getFromMmap(serverClientName, 1);
            int x, y;
            std::string serverLogin = getLogin(infoServer);
            std::string info = getCoord(infoServer, &x, &y);
            if(info == "Ранил") {
                ++count;
            }
            if(login != serverLogin) {
                battleInfo(ships, x, y, info);
            } else {
                battleInfo(enemyShips, x, y, info);
            }
            std::cout << "Ваше поле" << std::endl;
            printMap(ships);
            std::cout << std::endl;
            std::cout << "Поле противника" << std::endl;
            printMap(enemyShips);
            std::cout << std::endl;
            std::cout << infoServer<< std::endl;
            std::cout << std::endl;
            usleep(200000);
            setSemaphore(semaphore, &state, 0);
            usleep(25000);
        } else if (state == 6) { // игра завершилась
            std::string win = getFromMmap(serverClientName, 1);
            if(login != win) {
                std::cout << "\n Вы проиграли" << std::endl;
            } else {
                std::cout << "\n Вы выиграли" << std::endl;
            }
            flag = 0;
        }
    }
}

