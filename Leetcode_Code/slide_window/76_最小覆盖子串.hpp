class Solution {
public:
	// 将英文字母映射到hash表中
    char char_int(char c) {
        if (c >= 'A' && c <= 'Z') c -= 'A';
        else c = c - 'a' + 26;
        return c;
    }
	// 最小覆盖子串
	string minWindow(string s, string t) {
		int hash1[52] = { 0 }, hash2[52] = { 0 };
		int start = 0, n = s.size(), m = t.size(), len = INT_MAX;
		for (auto it : t) hash2[char_int(it)]++;
		for (int left = 0, right = 0, count = 0; right < n; ++right) {
			char in = s[right];
			if (hash2[char_int(in)] >= ++hash1[char_int(in)]) count++;
			//hash1[char_int(s[right])]++;
			if (count >= m) {
				if (right - left < len) {
					len = right - left;
					start = left;
				}
				while (count >= m) {
					char out = s[left++];
					if (hash2[char_int(out)] >= hash1[char_int(out)]--) count--;
				}
				
			}
		}
		return len == INT_MAX ? "" : s.substr(start, len + 1);
	}
};