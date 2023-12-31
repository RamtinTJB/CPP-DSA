#ifndef CPP_DSA_QUICKSORT_H_
#define CPP_DSA_QUICKSORT_H_

#include <algorithm>
#include <iterator>

template <typename RandomIt>
inline RandomIt partition(RandomIt start, RandomIt end) {
    auto i = start-1;
    auto pivot = *(end - 1);

    for (auto j = start; j != end-1; ++j) {
        if (*j <= pivot) {
            ++i;
            std::iter_swap(i, j);
        }
    }

    ++i;
    std::iter_swap(i, end-1);

    return i;
}

template <typename RandomIt>
inline void quicksort(RandomIt start, RandomIt end) {
    if (start >= end) return;

    auto p = partition(start, end);

    quicksort(start, p);
    quicksort(p+1, end);
}

#endif
