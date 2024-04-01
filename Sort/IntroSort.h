#ifndef CPP_DSA_INTROSORT_H_
#define CPP_DSA_INTROSORT_H_

#include "QuickSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"

#include <cmath>
#include <iterator>

template <typename RandomIt>
inline void introsort_(RandomIt start, RandomIt end, int maxDepth) {
    auto n = end - start;
    if (n < 16)
        insertionsort(start, end);
    else if (maxDepth == 0)
        heapsort(start, end);
    else {
        auto median = median_of_three(start, end-1, start + (end-start) / 2);
        std::iter_swap(median, end-1);

        auto p = partition(start, end);

        introsort_(start, p, maxDepth-1);
        introsort_(p+1, end, maxDepth-1);
    }
}

template <typename RandomIt>
inline void introsort(RandomIt start, RandomIt end) {
    auto maxDepth = std::log2(end - start) * 2;
    introsort_(start, end, maxDepth);
}

#endif
