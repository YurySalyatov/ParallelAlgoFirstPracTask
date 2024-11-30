#include <vector>
#include <thread>

const int SIZE = 1e8;
const int n = 50;
const int B = SIZE / (2 * n);


void sequentiallQuickSort(std::vector<int>& arr, int left, int right) {
    if (right <= left) return;
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[right]);
    int partitionIndex = i;
    sequentiallQuickSort(arr, left, partitionIndex - 1);
    sequentiallQuickSort(arr, partitionIndex + 1, right);
}

void parallelQuickSort(std::vector<int>& arr, int left, int right) {
    if (right - left <= B) {
        sequentiallQuickSort(arr, left, right);
        return;
    }
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[right]);
    int partitionIndex = i;
    auto t1 = std::thread([&, left, partitionIndex] {
        parallelQuickSort(arr, left, partitionIndex - 1);
        });
    auto t2 = std::thread([&, right, partitionIndex] {
        parallelQuickSort(arr, partitionIndex + 1, right);
        });
    t1.join();
    t2.join();
}