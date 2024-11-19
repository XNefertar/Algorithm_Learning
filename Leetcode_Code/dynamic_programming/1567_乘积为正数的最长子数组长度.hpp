class Solution {
public:

    int getMaxLen(vector<int>& nums) {
        int n =nums.size();
        // f -> 正数
        // g -> 负数
        vector<int> f(n, 0), g(n, 0);
        nums[0] == 0 ? (f[0] = g[0] = 0) : (nums[0] > 0 ? (f[0] = 1, g[0] = 0) : (f[0] = 0, g[0] = 1));
        
        for(int i = 1; i < n; ++i)
        {
            if(nums[i] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] > 0 ? g[i - 1] + 1 : 0;
            }
            else if(nums[i] < 0)
            {
                f[i] = g[i - 1] > 0 ? g[i - 1] + 1 : 0;
                g[i] = f[i - 1] + 1;
            }
            else
            {
                f[i] = g[i] = 0;
            }
        }
        
        return *max_element(f.begin(), f.end());
    }
};