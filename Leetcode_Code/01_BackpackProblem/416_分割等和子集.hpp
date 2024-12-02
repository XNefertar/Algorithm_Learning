class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(), sum = 0;
        for (auto it : nums) sum += it;
        
        // 判断总和是否为偶数
        if (sum % 2 != 0) return false;

        sum /= 2;  // 目标是将子集和为 sum / 2
        
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
        dp[0][0] = true;  // 空集的和为0，必然成立

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= sum; ++j) {
                // 不选当前数字 nums[i - 1] 或者选择当前数字
                dp[i][j] = dp[i - 1][j] || (j >= nums[i - 1] && dp[i - 1][j - nums[i - 1]]);
            }
        }

        return dp[n][sum];
    }
};