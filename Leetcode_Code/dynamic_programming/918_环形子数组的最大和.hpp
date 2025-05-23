class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size(), sum = 0;
        vector<int> f(n, 0), g(n, 0);
        for(auto it : nums){
            sum += it;
        }
        f[0] = g[0] = nums[0];
        for(int i = 1; i < n; ++i){
            f[i] = max(f[i - 1] + nums[i], nums[i]);
            g[i] = min(g[i - 1] + nums[i], nums[i]);
        }
        return max(*max_element(f.begin(), f.end()),\
         (sum - *min_element(g.begin(), g.end())) == 0\
          ? *max_element(g.begin(), g.end()) \
          : sum - *min_element(g.begin(), g.end()));
    }
};