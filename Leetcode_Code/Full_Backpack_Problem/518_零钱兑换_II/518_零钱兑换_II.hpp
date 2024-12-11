class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        // dp[i][j]
        // 表示到第i个位置
        // 凑成总金额j的最小硬币个数
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            for(int j = 0; j <= amount; ++j){
                if(j - coins[i - 1] >= 0){
                    dp[i][j] = (long long)dp[i - 1][j] + (long long)dp[i][j - coins[i - 1]];
                }
                else{
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][amount];
    }
};