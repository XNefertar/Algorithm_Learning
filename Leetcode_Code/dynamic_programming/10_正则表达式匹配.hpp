class Solution {
public:
    bool isMatch(string s, string p) {
        int n1 = s.size(), n2 = p.size();
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for(int j = 2; j <= n2; ++j){
            if(p[j - 1] == '*' && dp[0][j - 2])
                dp[0][j] = true;
        }
        
        for(int i = 1; i <= n1; ++i){
            for(int j = 1; j <= n2; ++j){
                if(p[j - 1] == '*' && j >= 2){
                    if(p[j - 2] == '.'){
                        dp[i][j] = dp[i][j - 2] || dp[i - 1][j];
                    }
                    else{
                        dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && s[i - 1] == p[j - 2]);
                    }
                }
                else{
                    dp[i][j] = (s[i - 1] == p[j - 1] ? dp[i - 1][j - 1] : \
                    (p[j - 1] == '.' ? dp[i - 1][j - 1] : false));
                }
            }
        }
        return dp[n1][n2];
    }
};