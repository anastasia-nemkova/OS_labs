#include <gtest/gtest.h>

#include <bitonic-sort.hpp>
#include <cmath>
#include <chrono>

std::vector<int> GenerateArray(int n) {
    std::vector<int> result(n);
    srand(static_cast<unsigned>(time(nullptr)));
    for(int i = 0; i < n; ++i) {
        result[i] = std::rand() % 100;
    }
    return result;
}


TEST(SecondLabTests, SingleThreadSort) {
    std::vector<int> a = {4, 5, 3, 1};
    std::vector<int> a_sorted = a;
    std::sort(a_sorted.begin(), a_sorted.end());
    sort(a, 1, 1);
    EXPECT_EQ(a, a_sorted);

    std::vector<int> b = {8, 6, 1, 4, 2, 9, 1, 4};
    std::vector<int> b_sorted = b;
    std::sort(b_sorted.begin(), b_sorted.end());
    sort(b, 1, 1);
    EXPECT_EQ(b,  b_sorted);
    
    std::vector<int> c = {8, 6, 1, 4, 2, 9, 1, 4};
    std::vector<int> c_sorted = c;
    std::sort(c_sorted.begin(), c_sorted.end(), std::greater<int>());
    sort(c, 0, 1);
    EXPECT_EQ(c, c_sorted);
}

TEST(SecondLabTest, MultithreadedSort) {
    auto performTestForGivenSize = [](int n, int maxThreadCount) {
        auto result = GenerateArray(n);
        auto sorted = result;
        sort(result, 1, maxThreadCount);
        std::sort(sorted.begin(), sorted.end());
        EXPECT_EQ(sorted, result);
    };

    performTestForGivenSize(4, 2);
    performTestForGivenSize(8, 4);
    performTestForGivenSize(1024, 6);
    performTestForGivenSize(32768, 10);
}

TEST(SecondLabTest, TimeSort) {
    auto getAvgTime = [](int threadCount) {
        int size_arr = std::pow(2, 23);
        auto arr = GenerateArray(size_arr);

        auto begin = std::chrono::high_resolution_clock::now();
        sort(arr, 1, threadCount);
        auto end = std::chrono::high_resolution_clock::now();
        double result = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        return result;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(4);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 4 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}