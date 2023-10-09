#include <vector>
#include <string>
#include <cassert>

using namespace std;

int LongestCommonSubsequence(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = 1+dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[n][m];
}

int main(int argc, const char** argv) {
    assert(LongestCommonSubsequence("abcde", "ace") == 3);
    assert(LongestCommonSubsequence("abc", "abc") == 3);
    assert(LongestCommonSubsequence("abc", "def") == 0);
    
    return 0;
}
