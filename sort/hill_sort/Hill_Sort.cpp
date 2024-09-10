#include "Hill_Sort.hpp"


void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Hill_Sort(std::vector<int>& nums){
  int n = nums.size();
  int gap = n;
  while(gap > 1)
    
    gap = gap / 3 + 1;
    for(int i = 0; i < n - gap; ++i){

      int end = i;
      int temp = nums[end + gap];
      while(end >= 0){
        if(nums[end] > temp){
          nums[end + gap] = nums[end];
          end -= gap;
        }
        else{
          break;
        }

      }
      nums[gap + end] = temp;
    }
    return nums;
}
