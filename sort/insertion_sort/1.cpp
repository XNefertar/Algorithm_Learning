#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

std::vector<int> nums(10001, 0);

void DataInit(){
    int index = 0;
    for(int i = 0; i < 10; ++i){
		srand(time(0));
		for (int j = 0; j < 1000; ++j) {
			nums[index++] = rand() % 10000;
		}
    }
}

void insertionSort1(vector<int>& nums){
	int n = nums.size();
	for(int i = 1; i < n; ++i){
		// 遍历已排序部分
		// 找到待插入位置
		int index = 0;
		for(; index < i; ++index){
			if(nums[index] > nums[i]) break;
		}
		int temp = nums[i], T_index = i;
		while(T_index >= index){
			nums[T_index] = nums[T_index - 1];
			--T_index;
		}
		nums[index] = temp;
	}
}

// 	Use binary search to optimize the lookup of insertion locations
void insertionSort2(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = 1; i < n; ++i) {
        // 使用二分查找查找待插入位置
        int left = 0, right = i;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[i]) right = mid;
			else left = mid + 1;
        }

        // 将元素 nums[i] 插入到找到的位置
        int temp = nums[i];
        for (int j = i; j > left; --j) {
            nums[j] = nums[j - 1];  // 元素右移
        }
        nums[left] = temp;  // 插入元素
    }
}

int main() {
    DataInit();

	vector<int> nums2 = nums;
    vector<int> nums1 = nums2;

    // 获取开始时间
    auto start = high_resolution_clock::now();
    // 执行插入排序S
    insertionSort1(nums2);
    // 获取结束时间
    auto end = high_resolution_clock::now();
    // 计算耗时
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken (Original) : " << duration.count() << " microseconds" << endl;


    // 获取开始时间
    start = high_resolution_clock::now();
    // 执行插入排序
    insertionSort2(nums1);
    // 获取结束时间
    end = high_resolution_clock::now();
    // 计算耗时
    duration = duration_cast<microseconds>(end - start);
    cout << "Time taken (Advanced) : " << duration.count() << " microseconds" << endl;
    return 0;
}