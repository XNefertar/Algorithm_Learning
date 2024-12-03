```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size(), sum = 0;
        for(auto it : nums) sum += it;
        target = (sum + target) / 2;
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= target; ++j){
                if(j >= nums[i - 1])
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
                else dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[n][target];
    }
};
```

