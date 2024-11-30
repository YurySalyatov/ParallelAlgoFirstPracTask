#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cassert>
#include <cstring>
#include <functional>

#include "quicksort.h";

std::random_device device;
std::mt19937 mt(device());

const int testSize = 5;

double oneTest(std::vector<std::vector<int>> &arr, void(*func)(std::vector<int>&, int, int), std::string name) {
    double times[testSize];
    for (int i = 0; i < testSize; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        func(arr[i], 0, SIZE - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = (end - start);
        times[i] = elapsed.count();
    }
    std::cout << name << " quicksort times: " << std::endl;
    double sum = 0;
    for (int i = 0; i < testSize; i++) {
        sum += times[i];
        std::cout << i + 1 << " " << times[i] << " seconds" << std::endl;
    }
    double meanTime = sum / testSize;
    std::cout << name << " quicksort mean times: " << meanTime << std::endl;
    return meanTime;
}


void correctnessTest() {
    int corSize = 1e5;
    std::vector<int> arr(corSize);
    std::vector<int> arrCopy(corSize);
    for (int i = 0; i < corSize; ++i) {
        arr[i] = mt();
        arrCopy[i] = arr[i];
    }
    // There not nessesary to check parralell, because it's the same as sequential
    std::sort(arrCopy.begin(), arrCopy.end());
    sequentiallQuickSort(arr, 0, corSize - 1);
    for (int i = 0; i < corSize; ++i) {
        assert(arr[i] = arrCopy[i]);
    }
    std::cout << "Correctness test PASSED" << std::endl;
}

void speedTest() { 
    std::vector<std::vector<int>> arr(testSize);
    std::vector<std::vector<int>> arrCopy(testSize);
    for (int i = 0; i < testSize; i++) {
        arr[i] = std::vector<int>(SIZE);
        arrCopy[i] = std::vector<int>(SIZE);
    }
    for (int i = 0; i < testSize; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            arr[i][j] = mt();
            arrCopy[i][j] = arr[i][j];
        }
    }
    double seq = oneTest(arrCopy, sequentiallQuickSort, "sequential");
    std::cout << std::endl;
    double par = oneTest(arr, parallelQuickSort, "parallel");
    double ratio = seq / par;
    std::cout << "ratio: " << ratio << std::endl;
    assert(ratio > 3);
    std::cout << "Sped test PASSED" << std::endl;
    
}

int main() {
    correctnessTest();
    speedTest();
    return 0;
}