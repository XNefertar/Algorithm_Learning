class Solution {
public:
    int totalFruit(vector<int>& f) {
        // unordered_map<int, int> hash;
        int hash[100001]{};
        int left = 0, right = 0, n = f.size(), ans = 0, kinds = 0;
        while(right < n){
            if(hash[f[right]] == 0) ++kinds;
            hash[f[right]]++;
            while(kinds > 2){
                hash[f[left]]--;
                if(hash[f[left]] == 0) kinds--;
                left++;
            }
            ans = std::max(ans, right - left + 1);
            right++;
        }
        return ans;
    }
};