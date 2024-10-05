class Solution {
public:
    
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double sum = 0, max = 0;
        if(n == 1){
            return nums[0];
        }
        int left = 0, right = left + k - 1;
        for(int i = left; i <= right; ++i){
            sum += nums[i];
        }
        max = sum;
        while(right < n){
            sum += nums[++right];
            sum -= nums[left++];
            max = sum > max ? sum : max;
        }
        return max / k;
    }
};