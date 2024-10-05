#include <iterator>
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int ans = 0, left = 0, right = 0, num_0 = 0, n = nums.size();
        while (right < n) {
            if (nums[right] == 0) num_0++; // 遇到0时增加计数
            while (num_0 > k) { // 当0的数量超过k时
                if (nums[left] == 0) num_0--; // 左指针移动时减少0的计数
                left++; // 移动左指针
            }
            ans = max(ans, right - left + 1); // 更新最大长度
            right++; // 移动右指针
        }
        return ans;
    }
};