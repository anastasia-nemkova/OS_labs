#include "/home/arnemkova/OS_labs/lab4/include/realizations.hpp"

#include <iostream>
#include <sstream>


void mainRoutine(const std::string& command) {
    std::istringstream iss(command);
    int operation;
    iss >> operation;

    if (operation == 1) {
        float arg1, arg2;
        iss >> arg1 >> arg2;
        float result = Derivative(arg1, arg2);
        std::cout << "Result of Derivative: " << result << std::endl;
    } else if (operation == 2) {
        float arg1, arg2;
        iss >> arg1 >> arg2;
        float result = Square(arg1, arg2);
        std::cout << "Result of Square: " << result << std::endl;
    } else {
        std::cout << "Invalid command." << std::endl;
    }
}

int main() {
    std::string command;

    while (true) {
        std::cout << "Enter command (0 to exit): ";
        std::getline(std::cin, command);

        if (command == "0") {
            break;
        }

        mainRoutine(command);
    }

    return 0;
}
