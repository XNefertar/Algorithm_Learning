class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size(), Max = 2;
        unordered_map<int, int> hash;
        vector<vector<int>> dp(n, vector<int>(n, 2));
        hash[nums[0]] = 0;
        for(int i = 1; i < n; ++i){
            for(int j = i + 1; j < n; ++j){
                int target = 2 * nums[i] - nums[j];
                if(hash.count(target)){
                    dp[i][j] = dp[hash[target]][i] + 1;
                }
                Max = max(Max, dp[i][j]);
            }
            hash[nums[i]] = i;
        }
        return Max;
    }
};o