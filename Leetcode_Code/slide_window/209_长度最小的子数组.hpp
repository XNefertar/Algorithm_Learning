class Solution {
public:
    
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), sum = 0, len = INT_MAX;
        for(int left = 0, right = 0; right < n; ++right){
            sum += nums[right];
            while(left <= right && sum >= target){
                len = std::min(right - left + 1, len);
                ++left;
                sum -= nums[left - 1];
            }
        }
        return len == INT_MAX ? 0 : len;
    }
};
