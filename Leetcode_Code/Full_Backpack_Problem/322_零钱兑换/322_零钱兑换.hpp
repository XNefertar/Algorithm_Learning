class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        // dp[i][j]
        // 表示到第i个位置
        // 凑成总金额j的最小硬币个数
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

        for(int j = 1; j <= amount; ++j){
            dp[0][j] = -1;
        }

        for(int i = 1; i <= n; ++i){
            for(int j = 0; j <= amount; ++j){
                if(j - coins[i - 1] >= 0 && dp[i][j - coins[i - 1]] != -1){
                    int temp = min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
                    dp[i][j] = temp == -1 ? dp[i][j - coins[i - 1]] + 1 : temp;
                }
                else{
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][amount];
    }
};