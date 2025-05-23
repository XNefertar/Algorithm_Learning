class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return 0;
        vector<int> dp(n, 0);

        for(int i = 2; i < n; ++i)
        {
            if(nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                dp[i] = dp[i - 1] + 1;
            }
            else 
            {
                dp[i] = 0;
            }
        }
        int sum = 0;
        for(auto it : dp)
        {
            sum += it;
        }
        return sum;
    }
};