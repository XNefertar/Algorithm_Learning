#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <windows.h>  // 用于控制台编码设置
#include "BloomFilter.hpp"

int main() {
    // 设置控制台编码为UTF-8，以正确显示中文
    SetConsoleOutputCP(65001);

    std::cout << "===== 布隆过滤器测试程序 =====\n" << std::endl;
    
    // 创建一个布隆过滤器，位数组大小为10000，使用3个哈希函数
    BloomFilter<std::string> filter(10000, 3);
    
    // 测试1: 添加和检查字符串元素
    std::cout << "测试1: 添加和检查字符串元素" << std::endl;
    std::vector<std::string> fruits = {
        "苹果", "香蕉", "橙子", "西瓜", "葡萄",
        "芒果", "樱桃", "草莓", "蓝莓", "柠檬"
    };
    
    // 添加水果名称
    std::cout << "添加元素:" << std::endl;
    for (const auto& fruit : fruits) {
        filter.addElement(fruit);
        std::cout << "  已添加: " << fruit << std::endl;
    }
    
    // 检查已添加的水果名称
    std::cout << "\n检查已添加的元素:" << std::endl;
    for (const auto& fruit : fruits) {
        bool found = filter.isContains(fruit);
        std::cout << "  " << fruit << ": " << (found ? "存在" : "不存在") << std::endl;
    }
    
    // 测试2: 检查未添加的元素
    std::cout << "\n测试2: 检查未添加的元素" << std::endl;
    std::vector<std::string> vegetables = {
        "白菜", "胡萝卜", "土豆", "黄瓜", "茄子"
    };
    
    int falsePositives = 0;
    for (const auto& vegetable : vegetables) {
        bool found = filter.isContains(vegetable);
        std::cout << "  " << vegetable << ": " << (found ? "存在 (假阳性!)" : "不存在") << std::endl;
        if (found) falsePositives++;
    }
    
    // 计算实际假阳性率
    double actualFalsePositiveRate = static_cast<double>(falsePositives) / vegetables.size();
    std::cout << "\n实际假阳性率: " << (actualFalsePositiveRate * 100) << "%" << std::endl;
    
    // 输出统计信息
    filter.printStats();
    
    // 测试3: 测试整数类型
    std::cout << "\n测试3: 测试整数类型" << std::endl;
    BloomFilter<int> intFilter(1000, 4);
    
    // 添加一些随机整数
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    std::vector<int> addedNumbers;
    std::cout << "添加20个随机整数:" << std::endl;
    for (int i = 0; i < 20; ++i) {
        int num = dis(gen);
        addedNumbers.push_back(num);
        intFilter.addElement(num);
        std::cout << "  已添加: " << num << std::endl;
    }
    
    // 验证添加的整数
    std::cout << "\n验证已添加的整数:" << std::endl;
    for (int num : addedNumbers) {
        bool found = intFilter.isContains(num);
        std::cout << "  " << num << ": " << (found ? "存在" : "不存在") << std::endl;
    }
    
    // 测试4: 测试清空功能
    std::cout << "\n测试4: 测试清空功能" << std::endl;
    filter.clearElement();
    std::cout << "布隆过滤器已清空" << std::endl;
    
    // 检查清空后是否找不到之前添加的元素
    std::cout << "清空后检查之前的元素:" << std::endl;
    for (const auto& fruit : fruits) {
        bool found = filter.isContains(fruit);
        std::cout << "  " << fruit << ": " << (found ? "存在 (错误!)" : "不存在 (正确)") << std::endl;
    }
    
    // 显示清空后的统计信息
    filter.printStats();
    
    std::cout << "\n===== 测试程序结束 =====" << std::endl;
    return 0;
}