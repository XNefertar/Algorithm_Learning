#include "AVLTree.hpp"
#include <iostream>

void testRotations() {
    std::cout << "=== Testing Rotation Cases ===" << std::endl;
    
    // Test Left Rotation (LL)
    AVLTree llTree;
    std::cout << "Right Rotation Test:" << std::endl;
    llTree.insertNode(30);
    llTree.insertNode(20);
    llTree.insertNode(10); // Should trigger right rotation
    std::cout << "Inorder Traversal: ";
    llTree.printInorder();
    std::cout << "\nIs Balanced: " << (llTree.isBalanced() ? "Yes" : "No") << std::endl;
    std::cout << "Tree Height: " << llTree.getHeight() << std::endl << std::endl;
    
    // Test Right Rotation (RR)
    AVLTree rrTree;
    std::cout << "Left Rotation Test:" << std::endl;
    rrTree.insertNode(10);
    rrTree.insertNode(20);
    rrTree.insertNode(30); // Should trigger left rotation
    std::cout << "Inorder Traversal: ";
    rrTree.printInorder();
    std::cout << "\nIs Balanced: " << (rrTree.isBalanced() ? "Yes" : "No") << std::endl;
    std::cout << "Tree Height: " << rrTree.getHeight() << std::endl << std::endl;
    
    // Test Left-Right Rotation (LR)
    AVLTree lrTree;
    std::cout << "Left-Right Rotation Test:" << std::endl;
    lrTree.insertNode(30);
    lrTree.insertNode(10);
    lrTree.insertNode(20); // Should trigger left-right rotation
    std::cout << "Inorder Traversal: ";
    lrTree.printInorder();
    std::cout << "\nIs Balanced: " << (lrTree.isBalanced() ? "Yes" : "No") << std::endl;
    std::cout << "Tree Height: " << lrTree.getHeight() << std::endl << std::endl;
    
    // Test Right-Left Rotation (RL)
    AVLTree rlTree;
    std::cout << "Right-Left Rotation Test:" << std::endl;
    rlTree.insertNode(10);
    rlTree.insertNode(30);
    rlTree.insertNode(20); // Should trigger right-left rotation
    std::cout << "Inorder Traversal: ";
    rlTree.printInorder();
    std::cout << "\nIs Balanced: " << (rlTree.isBalanced() ? "Yes" : "No") << std::endl;
    std::cout << "Tree Height: " << rlTree.getHeight() << std::endl << std::endl;
}

void testLargerTree() {
    std::cout << "=== Testing Larger Tree ===" << std::endl;
    AVLTree tree;
    
    // Insert multiple values
    int values[] = {50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45, 55, 65, 75, 85};
    for (int val : values) {
        std::cout << "Inserting: " << val << std::endl;
        tree.insertNode(val);
    }
    
    std::cout << "Inorder Traversal: ";
    tree.printInorder();
    std::cout << "\nIs Balanced: " << (tree.isBalanced() ? "Yes" : "No") << std::endl;
    std::cout << "Tree Height: " << tree.getHeight() << std::endl;
}

int main() {
    std::cout << "AVL Tree Test Program\n" << std::endl;
    
    // Note: Fix printInorder issues in AVLTree.hpp before running
    
    // Test rotations
    testRotations();
    
    // Test larger tree
    testLargerTree();
    
    return 0;
}