#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <immintrin.h>
#include <benchmark/benchmark.h>

int simd_find(int* data, size_t size, int value) {
  size_t i = 0;
  auto value_vec = _mm256_set1_epi32(value);

  for (; i + 7 < size; i += 8) {
    auto data_vec = _mm256_loadu_si256((__m256i*)&data[i]);
    auto cmp = _mm256_cmpeq_epi32(data_vec, value_vec);

    int mask = _mm256_movemask_epi8(cmp);

    if (mask != 0) { // Found a match
      for (int j = 0; j < 8; ++j) {
        if (data[i+j] == value) {
          return i + j;
        }
      }
    }
  }

  for (; i < size; ++i) {
    if (data[i] == value) {
      return i;
    }
  }

  return -1;
}

std::vector<int> generate_random_vector(size_t size, int target) {
  std::vector<int> data(size);
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(1, 100);

  for (size_t i = 0; i < size; ++i) {
    data[i] = dist(rng);
  }

  data[size/2] = target; // The target has to exist in the array
                         
  return data;
}

static void BM_simd_find(benchmark::State& state) {
  auto size = state.range(0);
  int target = 50;
  auto data = generate_random_vector(size, target);

  for (auto _ : state) {
    int result = simd_find(data.data(), size, target);
    benchmark::DoNotOptimize(result);
  }
}

static void BM_std_find(benchmark::State& state) {
  auto size = state.range(0);
  int target = 50;
  auto data = generate_random_vector(size, target);

  for (auto _ : state) {
    auto result = std::find(data.begin(), data.end(), target);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(BM_simd_find)->Arg(1 << 20);
BENCHMARK(BM_std_find)->Arg(1 << 20);

BENCHMARK_MAIN();
