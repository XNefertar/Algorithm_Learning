class Solution {
public:
    // Use three-dimensional array to represent the dp table
    // With a very high complexity of time and space
    // Optimization relies on scrolling arrays, 
    // reducing the dimensionality of 3D arrays to 2D, 
    // thereby reducing temporal and spatial complexity
    int findMaxForm(vector<string>& strs, int m, int n) {
        // b -> '0'
        // c -> '1'
        int size = strs.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for(int i = 1; i <= size; ++i){
            int b = 0, c = 0;
            for(auto it : strs[i - 1]){
                if(it == '0') b++;
                else c++;
            }
            for (int j = m; j >= b; --j) {
                for (int k = n; k >= c; --k) {
                    dp[j][k] = max(dp[j][k], dp[j - b][k - c] + 1);
                }
            }
        }
        return dp[m][n];
    }
};