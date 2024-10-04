class Solution {
public:
    // int max_range(int left, int right, vector<int>& num){
    //     int max = INT_MIN;
    //     for(int i = left; i < right; ++i){
    //         if(num[i] > max) max = num[i];
    //     }
    //     return max;
    // }
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> slide_window;
        vector<int> ans;
        int n = nums.size();
        for(int i = 0; i < n; ++i){
            if(!slide_window.empty() && i - slide_window.front() >= k){
                slide_window.pop_front();
            }

            // 进入前判断
            while(!slide_window.empty() && nums[i] > nums[slide_window.back()]){
                // 删除尾端
                slide_window.pop_back();
            }
            // 判断结束进入
            // 双端队列，进行尾插
            slide_window.push_back(i);

            if(i >= k - 1){
                ans.push_back(nums[slide_window.front()]);
            }
        }
        return ans;
    }
};