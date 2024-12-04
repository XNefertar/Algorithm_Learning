class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        int ans = 0, child = 0, cookie = 0;
        while(child < g.size() && cookie < s.size()){
            if(s[cookie] >= g[child]){
                ans++;
                ++cookie;
                ++child;
            }
            else{
                ++cookie;
            }
        }
        return ans;
    }
};