#include "bitonic-sort.hpp"


void compAndSwap(std::vector<int> &a, int i, int j, int dir) {
    if (dir == (a[i] > a[j])) {
        std::swap(a[i], a[j]);
    }
}

void bitonicMerge(std::vector<int> &a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
            compAndSwap(a, i, i + k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

void bitonicSort(std::vector<int> &a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(a, low, k, 1);
        bitonicSort(a, low + k, k, 0);
        bitonicMerge(a, low, cnt, dir);
    }
}

void* parallelBitonicSort(void* arg) {
    Data* data = static_cast<Data*>(arg);
    std::vector<int>& a = data->a;
    int low = data->low;
    int cnt = data->cnt;
    int dir = data->dir;
    int maxThreads = data->maxThreads;

    if (cnt > 1) {
        if (maxThreads == 1 || cnt <= 2) {
            bitonicSort(a, low, cnt, dir);
        } else {
            int k = cnt / 2;
            pthread_t t1, t2;
            Data data1 = {a, low, k, 1, maxThreads / 2};
            Data data2 = {a, low + k, k, 0, maxThreads / 2};
            pthread_create(&t1, nullptr, parallelBitonicSort, &data1);
            pthread_create(&t2, nullptr, parallelBitonicSort, &data2);
            pthread_join(t1, nullptr);
            pthread_join(t2, nullptr);
            bitonicMerge(a, low, cnt, dir);
        }
    }
    return nullptr;
}

void sort(std::vector<int> &a, int up, int maxThreads) {
    int n = a.size();
    Data data = {a, 0, n, up, maxThreads};
    parallelBitonicSort(&data);
}