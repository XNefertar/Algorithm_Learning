class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		int size2 = words[0].size(), size1 = s.size(), size3 = words.size();
		vector<int> res;
		unordered_map<string, int> hash1, hash2;
		// 构建hash表
		// 标识words中的单词出现的次数
		for (auto it : words) hash2[it]++;
		for (int h = 0; h < size2; ++h) {
			int count = 0;
			for (int left = h, right = h; right < size1; right += size2) {
				// 进入哈希表
				string str = s.substr(right, size2);
				hash1[str]++;
				count++;

				if (count == size3) {
					// 判断是否相等
					count -= 1;
					if (hash1 == hash2) {
						res.push_back(left);
					}
					// 移动左指针
					string str1 = s.substr(left, size2);
					hash1[str1]--;
					if (hash1[str1] == 0) hash1.erase(str1);
					left += size2;
				}
			}
			hash1.clear();
		}
		return res;
	}
};