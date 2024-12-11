class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        // dp[i][j]
        // 表示到第i个位置
        // 凑成总金额j的最小硬币个数
        vector<int> dp(amount + 1);
        const int INF = 0x3f3f3f;
        for(int j = 1; j <= amount; ++j){
            dp[j] = INF;
        }

        for(int i = 1; i <= n; ++i){
            for(int j = coins[i - 1]; j <= amount; ++j){
                if(dp[j - coins[i - 1]] < INF){
                    dp[j] = min(dp[j], dp[j - coins[i - 1]] + 1);
                }
            }
        }
        return dp[amount] >= INF ? -1 : dp[amount];
    }
};