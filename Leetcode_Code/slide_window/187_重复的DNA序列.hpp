class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> hash;
        vector<string> ans;
        int n = s.size();
        for(int left = 0, right = left + 9; right < n; ++right, ++left){
            string in = s.substr(left, right - left + 1);
            std::cout << in << std::endl;
            // 入哈希表 + 判断
            if(++hash[in] >= 2 && hash[in] < 3){
                ans.push_back(in);
            }
        }
        return ans;
    }
};