class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size(), Max = 0;
        unordered_map<int, int> hash;
        // 初始化hash表
        // 建立 值 -> 下标 的映射关系
        hash[arr[0]] = 0;
        hash[arr[1]] = 1;
        
        vector<vector<int>> dp(n, vector<int>(n, 2));
        for(int i = 2; i < n; ++i)
        {
            hash[arr[i]] = i;
            for(int j = 1; j < i; ++j)
            {
                int target = arr[i] - arr[j];
                if(hash.find(target) != hash.end() && hash[target] < j)
                {
                    dp[j][i] = dp[hash[target]][j] + 1;
                    Max = max(dp[j][i], Max);
                }
            }
        }

        return Max == 2 ? 0 : Max;
    }
};