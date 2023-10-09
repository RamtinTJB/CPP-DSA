#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int fib(int n) {
    if (n <= 1) return n;

    vector<int> dp(n+1, 0);
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

int main(int argc, const char** argv) {
    assert((fib(4) == 3));
    assert((fib(9) == 34));

    return 0;
}
