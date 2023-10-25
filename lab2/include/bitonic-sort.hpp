#pragma once

#include <iostream>
#include <vector>
#include <pthread.h>

extern pthread_mutex_t mtx;

struct Data {
    std::vector<int>& a;
    int low; // нижний индекс массива
    int cnt; //количество элементов
    int dir; // 1 - по возрастанию; 0 - по убыванию
    int maxThreads;
};

void compAndSwap(std::vector<int>& a, int i, int j, int dir);
void bitonicMerge(std::vector<int>& a, int low, int cnt, int dir);
void bitonicSort(std::vector<int>& a, int low, int cnt, int dir) ;
void* parallelBitonicSort(void* arg);
void sort(std::vector<int> &a, int up, int maxThreads);