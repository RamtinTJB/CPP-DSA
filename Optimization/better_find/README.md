# Optimized `find` algorithm

In this code I attempted to implement a faster version of `std::find` using SWAR (SIMD Within a Register) operations. I also compared my implementation with `std::find` in the standard library using Google Benchmark to measure the performance

## Algorithm Explanation

`simd_find` function processes 8 integers at a time instead of one at a time (what `std::find` does). Here are a summary of the steps:
- Load 8 integers from the array into the AVX2 register using the `_mm256_loadu_si256`
- Compare those 8 values with a register containing 8 copies of the target we are trying to find using `_mm256_cmpeq_epi32`
- The result of this operation is stored in a bit map and we can extract the most significant bit of each comparison result using `mm256_movemask_epi8`.
- If any of the bits in the resulting integer is set, it means that a match has been found and we can return the index

## Deep Dive into the Instructions Used

#### Loading the target using `_mm256_set1_epi32(int a)`
This instruction sets all the 32-bit integer lanes in the 256-bit vector to `a`
```cpp
auto value_vec = _mm256_set1_epi32(value);

// The above is roughly equivalent to:
for (int n = 0; n < 8; ++n) {
  dst[n] = a; // where dst is int*
}
```
#### Loading array data into a 256-bit vector using `_mm256_loadu_si256(const __m256i* mm_addr)`
This instruction loads 256 bits from memory address `mem_addr` into a vector and it supports unaligned memory addresses so it might be a little slower that the aligned version (`_mm256_load_si256`).

#### Performing the comparison using `_mm256_cmpeq_eip32(__m256i a, __m256i b)
- This operations compares each of the 8 pairs of 32-bit integers in `a` and `b`
- If any of the elements are equal, the result for that 32-bit line would be `0xFFFFFFFF` and if they are not equal, the result would be `0x00000000`.

#### Create a mask from the result using `_mm256_movemask_epi8(__m256i s)`
- This operation creates a mask from the most significant bit of each byte in the `s` vector.
- So `0xFFFFFFFF` would turn into 1111 in the return value of this function.
- This will allow us to quickly check if a match has been found (`mask != 0`).

## Further Improvements

There are ways to make this even faster that I'll briefly mention here. I'll implement and benchmark them in the future:

- using `_mm256_load_si256` to access memory faster due to alignment. In order to use this, we need ensure that data is aligned using memory allocation functions like `posix_memalign`.
- We can also eliminate the inner loop for when a match has been found and use bit manipulation instead to find the index of the match
```cpp
if (mask != 0) {
  int idx = __builtin_ctz(mask) / 4;
  return i + idx;
}
```
- We can use `_mm256_testz_si256` to test if all the bits of comparison result is zero without having to generate a mask every time.

## Usage

- Clone the repo
- Run using CMake
```sh
cmake -B build
cd build
make
./g_bench
```

## Result

For this benchmark I used MacBook Pro 2019, 2.3 GHz 8-Core Intel Core i9.

The `simd_find` function performed ~x6 better than `std::find` for an array containing ~1,000,000 random numbers with the target number being located exactly in the middle. The benchmark result is in the screenshot below:

![Benchmark](https://github.com/RamtinTJB/CPP-DSA/blob/main/Optimization/better_find/benchmark.jpg)
