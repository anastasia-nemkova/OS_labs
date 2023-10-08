#include "utils.hpp"

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        perror("Necessary arguments were not provided");
        exit(EXIT_FAILURE);
    }
    const char* fileName = argv[1];
    std::ofstream out(fileName);
    if(!out.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    std::string str;
    while (std::getline(std::cin, str)) {
        if (StartsWithCapital(str)) {
            out << str << std::endl;
        } else {
            std::string error  = "String: " + str + " - doesn't start with capital letter";
            std::cout << error << std::endl;
        }
    }
    exit(EXIT_FAILURE);
}   