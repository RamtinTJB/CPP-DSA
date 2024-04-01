#include <iostream>
#include <benchmark/benchmark.h>

void multiply(int fib[2][2], int mult[2][2]) {
  int a, b, c, d;
  a = fib[0][0] * mult[0][0] + fib[0][1] * mult[1][0];
  b = fib[0][0] * mult[0][1] + fib[0][1] * mult[1][1];
  c = fib[1][0] * mult[0][0] + fib[1][1] * mult[1][0];
  d = fib[1][0] * mult[0][1] + fib[1][1] * mult[1][1];

  fib[0][0] = a;
  fib[0][1] = b;
  fib[1][0] = c;
  fib[1][1] = d;
}

void power(int fib[2][2], int n) {
  if (n <= 1) return;

  power(fib, n/2);
  multiply(fib, fib);
  
  if (n & 1) {
    int m[2][2] = { {1, 1}, {1, 0} };
    multiply(fib, m);
  }
}

int fib_logn(int n) {
  if (n == 0) return 0;

  int f[2][2] = { {1, 1}, {1, 0} };
  power(f, n-1);

  return f[0][0];
}

int fib_rec(int n) {
  if (n <= 1) return n;
  return fib_rec(n-1) + fib_rec(n-2);
}

int fib_dp(int n) {
  if (n <= 1) return n;

  std::vector<int> dp(n+1, 0);
  dp[1] = 1;

  for (int i = 2; i <= n; ++i) {
    dp[i] = dp[i-1] + dp[i-2];
  }

  return dp[n];
}

static void FibonacciRecursive(benchmark::State& state) {
  for (auto _ : state)
    auto res = fib_rec(state.range(0));
}

static void FibonacciDP(benchmark::State& state) {
  for (auto _ : state)
    auto res = fib_dp(state.range(0));
}

static void FibonacciLogN(benchmark::State& state) {
  for (auto _ : state)
    auto res = fib_logn(state.range(0));
}

BENCHMARK(FibonacciRecursive)->DenseRange(0, 20, 4);
BENCHMARK(FibonacciDP)->DenseRange(0, 20, 4);
BENCHMARK(FibonacciLogN)->DenseRange(0, 20, 4);

BENCHMARK_MAIN();
