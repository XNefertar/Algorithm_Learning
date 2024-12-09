class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size(), sum = 0;
        for(auto it : stones) { sum += it; }
        
        vector<vector<int>> dp(n + 1, vector<int>(sum / 2 + 1, 0));
        for(int i = 1; i <= n; ++i){
            for(int j = 0; j <= sum / 2; ++j){
                if(j - stones[i - 1] >= 0){
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
                }
                else dp[i][j] = dp[i - 1][j];
            }
        }
        return sum - 2 * dp[n][sum / 2];
    }
};