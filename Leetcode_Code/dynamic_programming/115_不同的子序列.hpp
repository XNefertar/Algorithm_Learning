class Solution {
public:
    int numDistinct(string s, string t) {
        int n1 = t.size(), n2 = s.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for(auto &it : dp[0]){
            it = 1;
        }
        for(int i = 1; i <= n1; ++i){
            for(int j = 1; j <= n2; ++j){
                if(s[j - 1] == t[i - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + (dp[i][j - 1] % (long long)(10e9 + 7));
                }
                else{
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[n1][n2];
    }
};