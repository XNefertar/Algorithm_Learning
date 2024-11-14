class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for(int i = n - 1; i >= 0; --i)
            for(int j = i; j < n; ++j)
                if(s[i] == s[j])
                    dp[i][j] = i + 1 < j ? dp[i + 1][j - 1] : true;

        vector<int> ddp(n, INT_MAX);
        for(int i = 0; i < n; ++i){
            if(dp[0][i]) 
                ddp[i] = 0;
            else{
                for(int j = i; j > 0; --j){
                    if(dp[j][i]){
                        ddp[i] = min(ddp[j - 1] + 1, ddp[i]);
                    }
                }
            }
        }
        return ddp[n - 1];
    }
};