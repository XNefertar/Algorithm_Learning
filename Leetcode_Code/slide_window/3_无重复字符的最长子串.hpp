// 滑动窗口 + 哈希表
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int hash[128]{};
        int ans = 0;
        int left = 0, right = 0, n = s.size();
        while(right < n){
            hash[s[right]]++;
            while(hash[s[right]] > 1)
                hash[s[left++]]--;
            ans = std::max(ans, right - left + 1);
            right++;
        }
        return ans;
    }
};