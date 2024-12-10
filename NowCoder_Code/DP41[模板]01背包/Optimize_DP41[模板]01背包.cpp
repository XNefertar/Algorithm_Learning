#include <iostream>
#include <algorithm>
#include <vector>

// 优化版本
// 滚动数组
int main()
{
    int n, V, Max = 0;
    std::cin >> n >> V;
    
    // 0/1背包经典解法
    std::vector<int> dp1(V + 1);
    std::vector<int> volumn(n + 1), value(n + 1);
    
    // 读入数据
    for(int i = 1; i <= n; ++i){
        std::cin >> volumn[i] >> value[i];
    }
    
    for(int i = 1; i <= n; ++i){
        for(int j = V; j >= volumn[i]; --j){  // 从后往前遍历，避免重复计算
            dp1[j] = std::max(dp1[j], dp1[j - volumn[i]] + value[i]);
        }
    }
    std::cout << dp1[V] << std::endl;  // 输出最大值

    // 变种背包问题
    std::vector<int> dp2(V + 1);
    for(int j = 1; j <= V; ++j){
        dp2[j] = -1;
    }

    for(int i = 1; i <= n; ++i){
        for(int j = V; j >= volumn[i]; --j){
            if(dp2[j - volumn[i]] != -1) 
                dp2[j] = std::max(dp2[j], dp2[j - volumn[i]] + value[i]);
        }
    }

    std::cout << (dp2[V] == -1 ? 0 : dp2[V]) << std::endl;  // 输出最大值

    return 0;
}
