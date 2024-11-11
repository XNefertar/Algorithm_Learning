
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // f[i] 表示第i家必不抢
        // g[i] 表示第i家必抢
        vector<int> f(n + 1), g(n + 1);
        g[0] = nums[0];
        for(int i = 1; i < n; ++i){
            g[i] = f[i - 1] + nums[i];
            f[i] = max(f[i - 1], g[i - 1]);
        }
        return max(f[n - 1], g[n - 1]);
    }
};