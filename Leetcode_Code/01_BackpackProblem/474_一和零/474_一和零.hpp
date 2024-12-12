class Solution {
public:
    // Use three-dimensional array to represent the dp table
    // dp[i][j][k]
    // i -> position
    // j -> the number limit for '0'
    // k -> the number limit for '1'
    // The status representation: 
    // To the i position, the number of 0s does not exceed the length of the largest subset of j
    // and the number of 1s does not exceed k
    
    int findMaxForm(vector<string>& strs, int m, int n) {
        // b -> '0'
        // c -> '1'
        int size = strs.size();
        vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

        for(int i = 1; i <= size; ++i){
            for(int j = 0; j <= m; ++j){
                for(int k = 0; k <= n; ++k){
                    int b = 0, c = 0;
                    for(auto it : strs[i - 1]){
                        if(it == '0') b++;
                        else c++;
                    }        
                    if(j >= b && k >= c){
                        dp[i][j][k] = max(dp[i - 1][j - b][k -c] + 1, dp[i - 1][j][k]);
                    }
                    else dp[i][j][k] = dp[i - 1][j][k];
                }
            }
        }
        return dp[size][m][n];

    }
};