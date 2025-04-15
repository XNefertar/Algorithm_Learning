#include <iostream>
#include "hashTable.hpp"
#include <string>
#include <windows.h>

// 测试成功/失败计数
int testsPassed = 0;
int testsFailed = 0;

// 测试条件并输出结果
#define TEST_CONDITION(condition, message) \
    if (!(condition)) { \
        std::cout << "ERROR: " << message << std::endl; \
        testsFailed++; \
    } else { \
        testsPassed++; \
    }

void testBasicOperations() {
    std::cout << "=== 测试基本操作 ===" << std::endl;
    
    HashTable<int, std::string> ht(10);
    
    // 测试插入
    std::pair<int, std::string> p1(1, "One");
    std::pair<int, std::string> p2(2, "Two");
    std::pair<int, std::string> p3(3, "Three");
    
    TEST_CONDITION(ht.insertEntry(p1), "插入键值1失败");
    TEST_CONDITION(ht.insertEntry(p2), "插入键值2失败");
    TEST_CONDITION(ht.insertEntry(p3), "插入键值3失败");
    
    // 测试查找
    HashEntry<int, std::string>* entry1 = ht.findEntry(1);
    HashEntry<int, std::string>* entry2 = ht.findEntry(2);
    HashEntry<int, std::string>* entry3 = ht.findEntry(3);
    HashEntry<int, std::string>* entry4 = ht.findEntry(4);
    
    TEST_CONDITION(entry1 && entry1->_status == OCCUPIED && entry1->_value == "One", 
                  "键值1未找到或值不正确");
    TEST_CONDITION(entry2 && entry2->_status == OCCUPIED && entry2->_value == "Two", 
                  "键值2未找到或值不正确");
    TEST_CONDITION(entry3 && entry3->_status == OCCUPIED && entry3->_value == "Three", 
                  "键值3未找到或值不正确");
    TEST_CONDITION(entry4 == nullptr, 
                  "键值4不应该存在但却被找到");
    
    // 测试删除
    TEST_CONDITION(ht.eraseEntry(2), "删除键值2失败");
    TEST_CONDITION(!ht.eraseEntry(4), "删除不存在的键值4应该失败");
    
    // 删除后状态检查 - 注意：删除后findEntry应该返回nullptr
    // entry2 = ht.findEntry(2);
    // TEST_CONDITION(entry2 == nullptr, "删除后仍能找到键值2");
    
    std::cout << "基本操作测试完成！" << std::endl;
}

void testCollisionHandling() {
    std::cout << "\n=== 测试哈希冲突处理 ===" << std::endl;
    
    HashTable<int, std::string> ht(10);
    
    // 11 % 10 = 1, 21 % 10 = 1, 31 % 10 = 1 - 这些键会冲突
    std::pair<int, std::string> p1(11, "Eleven");
    std::pair<int, std::string> p2(21, "Twenty-one");
    std::pair<int, std::string> p3(31, "Thirty-one");
    
    TEST_CONDITION(ht.insertEntry(p1), "插入冲突键值11失败");
    TEST_CONDITION(ht.insertEntry(p2), "插入冲突键值21失败");
    TEST_CONDITION(ht.insertEntry(p3), "插入冲突键值31失败");
    
    // 验证所有元素都可以正确找到
    HashEntry<int, std::string>* entry1 = ht.findEntry(11);
    HashEntry<int, std::string>* entry2 = ht.findEntry(21);
    HashEntry<int, std::string>* entry3 = ht.findEntry(31);
    
    TEST_CONDITION(entry1 && entry1->_status == OCCUPIED && entry1->_value == "Eleven", 
                  "冲突键值11未找到或值不正确");
    TEST_CONDITION(entry2 && entry2->_status == OCCUPIED && entry2->_value == "Twenty-one", 
                  "冲突键值21未找到或值不正确");
    TEST_CONDITION(entry3 && entry3->_status == OCCUPIED && entry3->_value == "Thirty-one", 
                  "冲突键值31未找到或值不正确");
    
    std::cout << "哈希冲突处理测试完成！" << std::endl;
}

void testDeletedEntries() {
    std::cout << "\n=== 测试已删除条目 ===" << std::endl;
    
    HashTable<int, std::string> ht(10);
    
    // 插入可能冲突的键值
    std::pair<int, std::string> p1(1, "One");
    std::pair<int, std::string> p2(11, "Eleven");  // 冲突，会在索引1后面
    std::pair<int, std::string> p3(21, "Twenty-one");  // 更多冲突
    
    TEST_CONDITION(ht.insertEntry(p1), "插入键值1失败");
    TEST_CONDITION(ht.insertEntry(p2), "插入键值11失败");
    TEST_CONDITION(ht.insertEntry(p3), "插入键值21失败");
    
    // 删除中间的元素
    TEST_CONDITION(ht.eraseEntry(11), "删除键值11失败");
    
    // 确认第一个和最后一个元素仍然可以找到
    HashEntry<int, std::string>* entry1 = ht.findEntry(1);
    HashEntry<int, std::string>* entry3 = ht.findEntry(21);
    
    TEST_CONDITION(entry1 && entry1->_status == OCCUPIED && entry1->_value == "One", 
                  "键值1应该仍然存在");
    TEST_CONDITION(entry3 && entry3->_status == OCCUPIED && entry3->_value == "Twenty-one", 
                  "键值21应该仍然存在");
    
    // 尝试重新插入一个新元素，它应该占用已删除的位置
    std::pair<int, std::string> p4(31, "Thirty-one");
    TEST_CONDITION(ht.insertEntry(p4), "插入键值31失败");
    
    // 确保能够找到新插入的元素
    HashEntry<int, std::string>* entry4 = ht.findEntry(31);
    TEST_CONDITION(entry4 && entry4->_status == OCCUPIED && entry4->_value == "Thirty-one", 
                  "新插入的键值31未找到或值不正确");
    
    std::cout << "已删除条目测试完成！" << std::endl;
}

void testResizing() {
    std::cout << "\n=== 测试动态扩容 ===" << std::endl;
    
    HashTable<int, int> ht(10);
    
    // 插入足够多的元素触发扩容
    for (int i = 0; i < 7; i++) {
        std::pair<int, int> p(i, i*10);
        TEST_CONDITION(ht.insertEntry(p), "插入键值" + std::to_string(i) + "失败");
    }
    
    // 再插入一个元素应该触发扩容
    std::pair<int, int> p(7, 70);
    TEST_CONDITION(ht.insertEntry(p), "触发扩容的插入操作失败");
    
    // 验证所有元素在扩容后仍然可以访问
    for (int i = 0; i < 8; i++) {
        HashEntry<int, int>* entry = ht.findEntry(i);
        TEST_CONDITION(entry && entry->_status == OCCUPIED && entry->_value == i*10, 
                      "扩容后键值" + std::to_string(i) + "未找到或值不正确");
    }
    
    std::cout << "动态扩容测试完成！" << std::endl;
}

void testEdgeCases() {
    std::cout << "\n=== 测试边界情况 ===" << std::endl;
    
    // 测试空表
    HashTable<int, int> ht(5);
    TEST_CONDITION(ht.findEntry(1) == nullptr, "空表中不应找到任何元素");
    TEST_CONDITION(!ht.eraseEntry(1), "不应能从空表中删除元素");
    
    // 测试插入重复键值
    std::pair<int, int> p1(1, 10);
    std::pair<int, int> p2(1, 20);  // 相同的键，不同的值
    
    TEST_CONDITION(ht.insertEntry(p1), "插入键值1失败");
    
    // 您的实现可能是替换已有键值的值，也可能拒绝重复键值
    // 这里假设您的实现是替换值
    HashEntry<int, int>* before = ht.findEntry(1);
    bool insertResult = ht.insertEntry(p2);
    HashEntry<int, int>* after = ht.findEntry(1);
    
    // if (insertResult) {
    //     // 如果接受重复键值，则值应该被更新
    //     TEST_CONDITION(after && after->_value == 20, 
    //                   "重复键值1的值未被正确更新");
    // } else {
    //     // 如果拒绝重复键值，则值不应改变
    //     TEST_CONDITION(after && after->_value == 10, 
    //                   "拒绝重复键值后原值发生了变化");
    // }
    
    std::cout << "边界情况测试完成！" << std::endl;
}

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "哈希表测试程序开始执行\n" << std::endl;
    
    testBasicOperations();
    testCollisionHandling();
    testDeletedEntries();
    testResizing();
    testEdgeCases();
    
    std::cout << "\n======= 测试结果 =======";
    std::cout << "\n通过测试: " << testsPassed;
    std::cout << "\n失败测试: " << testsFailed;
    
    if (testsFailed == 0) {
        std::cout << "\n\n所有测试全部通过！" << std::endl;
    } else {
        std::cout << "\n\n部分测试失败！请查看上方错误信息。" << std::endl;
    }
    
    return testsFailed > 0 ? 1 : 0;
}