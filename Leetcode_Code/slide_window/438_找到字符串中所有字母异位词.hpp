class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int size1 = s.size(), size2 = p.size();
        if(size1 < size2) return {};
        int left = 0, right = left + size2 - 1;
        std::vector<int> hash1(26, 0), hash2(26, 0);
        for(auto it : p) hash2[it - 'a']++;
        std::vector<int> ans;
        for(int i = 0; i < size2; ++i){
            hash1[s[i] - 'a']++;
        }
        if(hash1 == hash2) ans.push_back(left);
        for(left = size2; left < size1; ++left){ 
            hash1[s[left] - 'a']++;
            hash1[s[left - size2] - 'a']--;
            if(hash1 == hash2) ans.push_back(left - size2 + 1);
        }
        return ans;
    }
};