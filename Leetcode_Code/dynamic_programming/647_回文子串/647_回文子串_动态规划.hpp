class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for(int i = n - 1; i >= 0; --i){
            for(int j = i; j < n; ++j){
                if(s[i] == s[j]){
                    if(i == j) dp[i][j] = 1;
                    else if(i + 1 == j) dp[i][j] = 1;
                    else dp[i][j] = dp[i + 1][j - 1];
                }
            }
        }
        int ans = 0;
        for(auto iit : dp){
            for(auto it : iit){
                if(it == true){
                    ans++;
                }
            }
        }
        return ans;
    }
};