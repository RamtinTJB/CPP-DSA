#include <iostream>
#include <fstream>
#include <benchmark/benchmark.h>
#include <climits>

auto coutbuff = std::cout.rdbuf();
std::fstream out("output.txt");

static void DoSetup(const benchmark::State& state) {
    // Redirect the output of cout to a local string stream
    // so the console doesn't get full with empty new lines
    std::cout.rdbuf(out.rdbuf());
}

static void DoTeardown(const benchmark::State& state) {
    // Restoring the cout to its original buffer so
    // we can view the output of google benchmark
    std::cout.rdbuf(coutbuff);
}

static void BM_Endl(benchmark::State& state) {
    for (auto _ : state) {
        for (auto i = 0; i < state.range(0); ++i)
            std::cout << std::endl;
    }
}

static void BM_BackslashN(benchmark::State& state) {
    for (auto _ : state) {
        for (auto i = 0; i < state.range(0); ++i)
            std::cout << '\n';
    }
}

BENCHMARK(BM_Endl)->RangeMultiplier(8)->Range(256, 2<<16)->Setup(DoSetup)->Teardown(DoTeardown);
BENCHMARK(BM_BackslashN)->RangeMultiplier(8)->Range(256, 2<<16)->Setup(DoSetup)->Teardown(DoTeardown);

BENCHMARK_MAIN();
