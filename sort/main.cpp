#include "Hill_Sort.hpp"
#include "Heap_Sort.hpp"
#include "Quick_Sort.hpp"

int main() {
    std::srand(std::time(0)); // 使用当前时间作为随机数生成种子

    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = std::rand() % 100; // 生成0到99之间的随机数
    }

    std::cout << "Array before sorting: ";
    printArray(arr);

    Quick_Sort(arr, 0, arr.size() - 1);

    std::cout << "Array after sorting: ";
    printArray(arr);

    return 0;
}
