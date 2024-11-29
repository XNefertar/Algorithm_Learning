#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int n, V, Max = 0;
    std::cin >> n >> V;
    
    // 0/1背包经典解法
    std::vector<std::vector<int>> dp1(n + 1, std::vector<int>(V + 1, 0));
    std::vector<int> volumn(n + 1), value(n + 1);
    
    // 读入数据
    for(int i = 1; i <= n; ++i){
        std::cin >> volumn[i] >> value[i];
    }
    
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= V; ++j){  // 从后往前遍历，避免重复计算
            dp1[i][j] = dp1[i - 1][j];
            if(j >= volumn[i]) dp1[i][j] = std::max(dp1[i][j], dp1[i - 1][j - volumn[i]] + value[i]);
        }
    }
    std::cout << dp1[n][V] << std::endl;  // 输出最大值

    // 变种背包问题
    std::vector<std::vector<int>> dp2(n + 1, std::vector<int>(V + 1, 0));
    for(int j = 1; j <= V; ++j){
        dp2[0][j] = -1;
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= V; ++j){
            dp2[i][j] = dp2[i - 1][j];
            if(j >= volumn[i] && dp2[i - 1][j - volumn[i]] != -1) 
                dp2[i][j] = std::max(dp2[i][j], dp2[i - 1][j - volumn[i]] + value[i]);
        }
    }

    std::cout << (dp2[n][V] == -1 ? 0 : dp2[n][V]) << std::endl;  // 输出最大值

    return 0;
}
