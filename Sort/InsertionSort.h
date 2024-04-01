#ifndef CPP_DSA_INSERTIONSORT_H_
#define CPP_DSA_INSERTIONSORT_H_

#include <algorithm>
#include <iterator>

template <typename RandomIt>
inline void insertionsort(RandomIt start, RandomIt end) {
    for (; start != end; ++start) {
        auto itMin = start;
        for (auto it = start+1; it != end; ++it) {
            if (*it < *itMin) {
                itMin = it;
            }
        }

        if (itMin != start) {
            std::iter_swap(itMin, start);
        }
    }
}

#endif
