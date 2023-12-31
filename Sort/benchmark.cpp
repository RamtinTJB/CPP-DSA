#include "HeapSort.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "IntroSort.h"

#include <vector>
#include <random>
#include <functional>
#include <benchmark/benchmark.h>

std::vector<int> vec(100000);

static void BM_IntroSort(benchmark::State& state) {
    std::vector<int> v(vec);
    for (auto _ : state) {
        introsort(v.begin(), v.end());
    }
}

static void BM_QuickSort(benchmark::State& state) {
    std::vector<int> v(vec);
    for (auto _ : state) {
        quicksort(v.begin(), v.end());
    }
}

static void BM_HeapSort(benchmark::State& state) {
    std::vector<int> v(vec);
    for (auto _ : state) {
        heapsort(v.begin(), v.end());
    }
}

BENCHMARK(BM_IntroSort);
BENCHMARK(BM_QuickSort);
BENCHMARK(BM_HeapSort);

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 10000);

    std::generate(vec.begin(), vec.end(), std::bind(dis, std::ref(mt)));

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}
