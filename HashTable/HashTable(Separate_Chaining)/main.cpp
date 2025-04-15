#include <iostream>
#include <string>
#include <windows.h>  // 用于控制台编码
#include "HashTable.hpp"

int main() {
    // 设置控制台编码为UTF-8
    SetConsoleOutputCP(65001);
    
    std::cout << "===== 拉链法哈希表测试 =====\n" << std::endl;
    
    // 创建一个整数->字符串的哈希表
    HashTable<int, std::string> ht(10);
    
    // 测试插入
    std::cout << "插入元素:" << std::endl;
    ht.addElement(std::make_pair(1, "一"));
    ht.addElement(std::make_pair(2, "二"));
    ht.addElement(std::make_pair(11, "十一"));  // 故意制造冲突(1和11)
    ht.addElement(std::make_pair(12, "十二"));  // 故意制造冲突(2和12)
    std::cout << "  插入了4个元素\n" << std::endl;
    
    // 测试查找
    std::cout << "查找元素:" << std::endl;
    std::string value;
    if(ht.findElement(1, value)) {
        std::cout << "  键1对应的值: " << value << std::endl;
    }
    
    if(ht.findElement(11, value)) {
        std::cout << "  键11对应的值: " << value << std::endl;
    }
    
    if(!ht.findElement(3, value)) {
        std::cout << "  键3不存在" << std::endl;
    }
    
    // 测试更新
    std::cout << "\n更新元素:" << std::endl;
    ht.addElement(std::make_pair(2, "贰"));
    if(ht.findElement(2, value)) {
        std::cout << "  键2更新后的值: " << value << std::endl;
    }
    
    // 测试删除
    // std::cout << "\n删除元素:" << std::endl;
    // if(ht.removeElement(11)) {
    //     std::cout << "  成功删除键11" << std::endl;
    // }
    
    if(!ht.findElement(11, value)) {
        std::cout << "  键11已被成功删除" << std::endl;
    }
    
    // 测试字符串键
    std::cout << "\n使用字符串键:" << std::endl;
    HashTable<std::string, int> strHt;
    strHt.addElement(std::make_pair("apple", 1));
    strHt.addElement(std::make_pair("banana", 2));
    strHt.addElement(std::make_pair("cherry", 3));
    
    int fruitValue;
    if(strHt.findElement("banana", fruitValue)) {
        std::cout << "  banana的值: " << fruitValue << std::endl;
    }
    
    return 0;
}