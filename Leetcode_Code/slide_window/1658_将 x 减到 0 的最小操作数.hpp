class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0, n = nums.size();
        for(auto it : nums) sum += it;
        int target = sum - x;
        if(target < 0) return -1;
        // if(target == 0) return n;
        int right = 0, left = 0, ans = -1, tmp_sum = 0;
        while(right < n){
            tmp_sum += nums[right];
            while(tmp_sum > target)
                tmp_sum -= nums[left++];
            if(tmp_sum == target) 
                ans = std::max(ans, right - left + 1);
            ++right;
        }
        if(ans == -1) return ans;
        else return n - ans;
    }
};