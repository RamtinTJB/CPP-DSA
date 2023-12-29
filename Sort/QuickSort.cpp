#include "sort.h"

int partition(std::vector<int>&, int, int);

void quicksort_(std::vector<int>& vec, int lo, int hi) {
    if (lo >= hi || lo < 0) return;
    
    // Partition the array
    int p = partition(vec, lo, hi);

    // Recursively do the same thing on the left and right
    // halves of the array
    quicksort_(vec, lo, p-1);
    quicksort_(vec, p+1, hi);
}

int partition(std::vector<int>& vec, int lo, int hi) {
    // Choose the last element as the pivot
    int pivot = vec[hi];

    // Temporary pivot index
    int i = lo-1;

    for (int j = lo; j < hi; ++j) {
        if (vec[j] <= pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }

    ++i;
    std::swap(vec[i], vec[hi]);

    return i;
}

void quicksort(std::vector<int>& vec) {
    quicksort_(vec, 0, vec.size()-1);
}
