class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), maxlen = 1, maxindex = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for(int i = n - 1; i >= 0; --i){
            for(int j = i; j < n; ++j){
                if(s[i] == s[j]){
                    dp[i][j] = i + 1 < j ? dp[i + 1][j - 1] : true;

                    if(dp[i][j] && j - i + 1 > maxlen){
                        maxlen = j - i + 1;
                        maxindex = i;
                    }
                }
            }
        }
        string ans(s, maxindex, maxlen);
        return ans;
    }
};