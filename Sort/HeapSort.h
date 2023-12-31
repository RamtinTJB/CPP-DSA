#ifndef CPP_DSA_HEAPSORT_H_
#define CPP_DSA_HEAPSORT_H_

#include <algorithm>
#include <iterator>

template <typename RandomIt>
void heapify(RandomIt start, RandomIt end, RandomIt root) {
    auto left = start + 2*(root-start) + 1;
    auto right = start + 2*(root-start) + 2;
    auto largest = root;

    if (left < end && *left > *largest)
        largest = left;

    if (right < end && *right > *largest)
        largest = right;

    if (largest != root) {
        std::iter_swap(root, largest);
        heapify(start, end, largest);
    }
}

template <typename RandomIt>
void heapsort(RandomIt start, RandomIt end) {
    for (auto it = start + (end-start)/2 - 1; it >= start; --it)
        heapify(start, end, it);

    for (auto it = end-1; it > start; --it) {
        std::iter_swap(start, it);
        heapify(start, it, start);
    }
}

#endif
