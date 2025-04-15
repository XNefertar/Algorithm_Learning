#include <iostream>
#include "RBTree.hpp"
#include <windows.h>

void printTreeStructure(TreeNode* node, std::string prefix = "", bool isLeft = false) {
    if (node == nullptr) return;
    
    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    std::cout << node->_value << "(" << (node->_color == RED ? "红" : "黑") << ")" << std::endl;
    
    printTreeStructure(node->_left, prefix + (isLeft ? "│   " : "    "), true);
    printTreeStructure(node->_right, prefix + (isLeft ? "│   " : "    "), false);
}

// 验证红黑树性质
bool verifyRBProperties(TreeNode* node, int& blackHeight) {
    if (node == nullptr) {
        blackHeight = 1; // 空节点是黑色
        return true;
    }
    
    // 验证红色节点的子节点是黑色
    if (node->_color == RED) {
        if ((node->_left && node->_left->_color == RED) || 
            (node->_right && node->_right->_color == RED)) {
            std::cout << "错误：红色节点 " << node->_value << " 有红色子节点！" << std::endl;
            return false;
        }
    }
    
    int leftBlackHeight = 0;
    int rightBlackHeight = 0;
    
    if (!verifyRBProperties(node->_left, leftBlackHeight) || 
        !verifyRBProperties(node->_right, rightBlackHeight)) {
        return false;
    }
    
    // 验证从当前节点到所有叶子节点的黑色节点数相同
    if (leftBlackHeight != rightBlackHeight) {
        std::cout << "错误：节点 " << node->_value << " 的左右子树黑高不同！"
                  << " 左:" << leftBlackHeight << "，右:" << rightBlackHeight << std::endl;
        return false;
    }
    
    blackHeight = leftBlackHeight + (node->_color == BLACK ? 1 : 0);
    return true;
}



int main() {
    SetConsoleOutputCP(65001);

    std::cout << "测试用例1：基本插入操作" << std::endl;
    RBTree tree1;
    
    // 基本插入
    tree1.insertNode(50);
    tree1.insertNode(30);
    tree1.insertNode(70);
    tree1.insertNode(20);
    tree1.insertNode(40);
    
    std::cout << "中序遍历结果：" << std::endl;
    tree1.printInOrder();


    std::cout << "测试用例2：左旋转测试（按升序插入）" << std::endl;
    RBTree tree2;
    
    // 升序插入（触发左旋转）
    for (int i = 10; i <= 100; i += 10) {
        std::cout << "插入: " << i << std::endl;
        tree2.insertNode(i);
        printTreeStructure(tree2.getTreeRoot());
        std::cout << "----------" << std::endl;
    }


    std::cout << "测试用例4：复杂平衡测试" << std::endl;
    RBTree tree3;
    
    // 按特定顺序插入，触发各种旋转情况
    int values[] = {41, 38, 31, 12, 19, 8, 25, 50, 49, 45, 60, 73, 66};
    int size = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < size; i++) {
        std::cout << "插入: " << values[i] << std::endl;
        tree3.insertNode(values[i]);
    }
    
    std::cout << "中序遍历结果：" << std::endl;
    tree3.printInOrder();
    
    // 验证红黑树性质
    int blackHeight = 0;
    bool isValid = verifyRBProperties(tree3.getTreeRoot(), blackHeight);
    std::cout << "树是否有效: " << (isValid ? "是" : "否") << std::endl;
    std::cout << "黑高: " << blackHeight << std::endl;
    

    std::cout << "测试用例5：边界情况测试" << std::endl;
    RBTree tree5;
    
    // 测试空树
    std::cout << "空树中序遍历：" << std::endl;
    tree5.printInOrder();
    
    // 测试插入单个节点
    std::cout << "插入根节点 50" << std::endl;
    tree5.insertNode(50);
    std::cout << "根节点颜色: " << (tree5.getTreeRoot()->_color == RED ? "红" : "黑") << std::endl;
    
    // 测试插入重复值
    std::cout << "尝试插入重复值 50：" << (tree5.insertNode(50) ? "成功" : "失败") << std::endl;
    
    // 插入更多节点
    tree5.insertNode(30);
    tree5.insertNode(70);
    std::cout << "中序遍历结果：" << std::endl;
    tree5.printInOrder();


    return 0;
}