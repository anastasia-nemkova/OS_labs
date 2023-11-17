#include <iostream>
#include <sstream>
#include <cstdlib>
#include <dlfcn.h>

using DerivativeFunc = float (*)(float, float);
using SquareFunc = float (*)(float, float);

void* loadLibrary(const std::string& libraryName) {
    void* handle = dlopen(libraryName.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    return handle;
}

void unloadLibrary(void* handle) {
    if (dlclose(handle) != 0) {
        std::cerr << "Cannot unload library: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char* pathToLib1 = getenv("PATH_TO_LIB1");
    const char* pathToLib2 = getenv("PATH_TO_LIB2");

    if (pathToLib1 == nullptr || pathToLib2 == nullptr) {
        std::cout << "PATH_TO_LIB1 or PATH_TO_LIB2 is not specified\n";
        exit(1);
    }


    void* libraryHandle = loadLibrary(pathToLib1);


    DerivativeFunc Derivative = (DerivativeFunc)dlsym(libraryHandle, "Derivative");
    SquareFunc Square = (SquareFunc)dlsym(libraryHandle, "Square");

    std::string command;

    while (true) {
        std::cout << "Enter command (0 to switch libraries, 1 or 2 to call functions, q to exit): ";
        std::getline(std::cin, command);

        if (command == "0") {
            unloadLibrary(libraryHandle);

            std::cout << "Enter library number (1 or 2): ";
            std::getline(std::cin, command);

            if (command == "1") {
                libraryHandle = loadLibrary(pathToLib1);
            } else if (command == "2") {
                libraryHandle = loadLibrary(pathToLib2);
            } else {
                std::cout << "Invalid library number.\n";
                exit(1);
            }

            Derivative = reinterpret_cast<DerivativeFunc>(dlsym(libraryHandle, "Derivative"));
            Square = reinterpret_cast<SquareFunc>(dlsym(libraryHandle, "Square"));

        } else if (command == "q") {
            break;

        } else {
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
    }

    unloadLibrary(libraryHandle);

    return 0;
}

// export PATH_TO_LIB1="/home/arnemkova/OS_labs/lab4/build/librealization1.so"
// export PATH_TO_LIB2="/home/arnemkova/OS_labs/lab4/build/librealization2.so"