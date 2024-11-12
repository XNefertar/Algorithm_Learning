class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& arr) {
        long long n = arr.size(), Max = 0;
        unordered_map<long long, vector<long long>> hash;
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        hash[arr[0]].push_back(0);
        for(int i = 1; i < n; ++i){
            for(int j = i + 1; j < n; ++j){
                long long tar = (long long)arr[i] - arr[j] + arr[i];
                if(hash.find(tar) != hash.end()){
                    auto vec = hash.find(tar)->second;
                    for(auto it : vec){
                        if(it < i)
                            dp[i][j] += dp[it][i] + 1;
                    }
                }
                Max += dp[i][j];
            }
            hash[arr[i]].push_back(i);
        }
        return Max;
    }
};