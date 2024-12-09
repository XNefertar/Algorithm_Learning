#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, V;
    cin >> n >> V;
    vector<int> value(n);
    vector<int> volumn(n);
    for (int i = 0; i < n; ++i) {
        cin >> volumn[i] >> value[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(V + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= V; ++j) {
            if (j - volumn[i - 1] >= 0) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - volumn[i - 1]] + value[i - 1]);
            } else dp[i][j] = dp[i - 1][j];
        }
    }

    std::cout << dp[n][V] << std::endl;


    // 变种背包问题
    std::vector<std::vector<int>> dp2(n + 1, std::vector<int>(V + 1, 0));
    for (int j = 1; j <= V; ++j) {
        dp2[0][j] = -1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= V; ++j) {
            if (j >= volumn[i - 1] && dp2[i][j - volumn[i - 1]] != -1)
                dp2[i][j] = max(dp2[i - 1][j], dp2[i][j - volumn[i - 1]] + value[i - 1]);
            else dp2[i][j] = dp2[i - 1][j];
        }
    }

    std::cout << (dp2[n][V] == -1 ? 0 : dp2[n][V]) << std::endl;  // 输出最大值

}