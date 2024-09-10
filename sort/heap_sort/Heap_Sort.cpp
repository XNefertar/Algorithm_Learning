#include "Heap_Sort.hpp"

void AdjustDown(std::vector<int>& nums, int size, int root){
  int n = size;
  int parent = root;
  int child = parent * 2 + 1;
  while(child < n){
    if(child + 1 < n && nums[child + 1] > nums[child]){
      ++child;
    }
    if(nums[child] > nums[parent]){
      std::swap(nums[child], nums[parent]);
    }
    else{
      break;
    }
    parent = child;
    child = parent * 2 + 1;
  }
}

std::vector<int> Heap_Sort(std::vector<int>& nums){
  int n = nums.size();
  for(int i = (n - 1 - 1) / 2; i >= 0; --i){
    AdjustDown(nums, n, i);
  }
  int end = n - 1;
  while(end > 0){
    std::swap(nums[end], nums[0]);
    AdjustDown(nums, end, 0);
    --end;
  }
  return nums;
}
