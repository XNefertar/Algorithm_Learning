#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 优化版本
// 滚动数组
int main() {
    int n, V;
    cin >> n >> V;
    vector<int> value(n);
    vector<int> volumn(n);
    for (int i = 0; i < n; ++i) {
        cin >> volumn[i] >> value[i];
    }

    vector<int> dp(V + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = volumn[i - 1]; j <= V; ++j) {
                dp[j] = max(dp[j], dp[j - volumn[i - 1]] + value[i - 1]);
        }
    }

    std::cout << dp[V] << std::endl;


    // 变种背包问题
    std::vector<int> dp2(V + 1, 0);
    for (int j = 1; j <= V; ++j) {
        dp2[j] = -1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = volumn[i - 1]; j <= V; ++j) {
            if (dp2[j - volumn[i - 1]] != -1)
                dp2[j] = max(dp2[j], dp2[j - volumn[i - 1]] + value[i - 1]);
        }
    }

    std::cout << (dp2[V] == -1 ? 0 : dp2[V]) << std::endl;  // 输出最大值

}