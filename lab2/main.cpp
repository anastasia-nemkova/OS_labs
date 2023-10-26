#include "bitonic-sort.hpp"


int main(int argc, char const *argv[]) {
    if (argc != 2){
        std::cout << "wrong arguments" << std::endl;
        return -1;
    }
    int maxThreads = std::atoi(argv[1]);
    
    int n;
    std::cout << "Size of arrive: ";
    std::cin >> n;
    std::vector<int> arr(n);

    std::cout << "Element of arrive: ";
    for(int i = 0; i < n; ++i){
        std::cin >> arr[i];
    }
    // up = 1 - сортировка по возрастанию
    // up = 0 - сортировка по убыванию
    int up = 1;
    sort(arr, up, maxThreads);

    std::cout << "Result:\n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}