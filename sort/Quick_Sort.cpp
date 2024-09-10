#include "Quick_Sort.hpp"
#include <vector>
#include <algorithm> // for std::swap

int Part_Sort(std::vector<int>& vec, int begin, int end) {
    int keyindex = end;
    int key = vec[keyindex];
    while (begin < end) {
        while (vec[begin] < key && begin < end) {
            ++begin;
        }
        while (vec[end] >= key && begin < end) { // 修改为 >=
            --end;
        }
        if (begin < end) { // 加一个条件判断，防止不必要的交换
            std::swap(vec[begin], vec[end]);
        }
    }
    std::swap(vec[begin], vec[keyindex]); // 交换的是vec中的元素
    return begin;
}

void Quick_Sort(std::vector<int>& vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int div = Part_Sort(vec, left, right);
    Quick_Sort(vec, left, div - 1);
    Quick_Sort(vec, div + 1, right);
}
