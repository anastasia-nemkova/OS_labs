#include "shared_memory.hpp"
#include "server_utils.hpp"


int main() {
    std::string input;
	std::vector<std::string> logins;
	std::map<std::string, int> statistic;
	int loginCount = 0;

	std::cout << "Введите логин" << std::endl;
	while (true) {
		std::cin >> input;
		if(input == "end") {
			break;
		}
		statistic[input] = 0;
		logins.push_back(input);
		++loginCount;
	}
	std::cout << "\nЛогины сохранены\n" << std::endl;

	while(true) {
		sem_unlink(generalSemName);
		sem_t* generalSem = OpenSemaphore(generalSemName, 1);
		int generalState = 1; //состояние семафора

		sem_unlink(startSemName);
		sem_t* startSem = OpenSemaphore(startSemName, 0);

		int loginCountGame = 0; // количество зарегистрированных пользователей
		std::vector<std::string> playersName(2);

		while(true) {
			if(loginCountGame == 2) {
				break;
			}
			sem_getvalue(generalSem, &generalState);
			if(generalState == 0) {
				std::string login = getFromMmap(clientServerName, 1);
				std::cout << login << " зарегистрирован" << std::endl;
				playersName[loginCountGame] = login;
				++loginCountGame;

				// проверка: игрок с таким логин существует и имена игроков не совпадают
				if(std::find(std::begin(logins), std::end(logins), login) != logins.end() && playersName[0] != playersName[1]) {
					giveToMmap("Успешная регистрация", serverClientName, generalSem, &generalState, 1);
				}
				setSemaphore(generalSem, &generalState, 2);
				usleep(25000);
			} else {
				usleep(500000);
			}
		}
		sem_close(generalSem);
		sem_destroy(generalSem);

		std::string str(10, '0');
		std::vector<std::vector<std::string>> twoMatrix(2, std::vector<std::string>(10, str));

		std::cout << playersName[0] << " против " << playersName[1] << std::endl;

		sem_unlink(generalSemName);
		usleep(1000000);

		shipLocation(playersName, twoMatrix, statistic);
		startGame(twoMatrix, playersName, startSem, statistic);

		usleep(5000000);


	}
}

