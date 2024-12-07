// Explanation
// 1. Why not use a one-dimensional dp table?
// You can't tell the status of the previous house through a 1D DP table - whether it was stolen or not
// Therefore, a two-dimensional dp table needs to be used to represent the current state
// Here I have made another optimization, using two 1D DP tables instead of 2D DP tables, which is easier to understand
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // The first one-dimensional dp table f[i] indicates that the ith family must not steal
        // The second one-dimensional dp table g[i] indicates that the ith family will definitely steal
        vector<int> f(n + 1), g(n + 1);
        g[0] = nums[0];
        for(int i = 1; i < n; ++i){
            // So there is a simple logical relationship between the two, from which the state transition equation can be derived
            g[i] = f[i - 1] + nums[i];
            f[i] = max(f[i - 1], g[i - 1]);
        }
        return max(f[n - 1], g[n - 1]);
    }
};