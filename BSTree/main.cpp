#include <iostream>
#include "BSTree.hpp"

void testInsert(BST& tree) {
    std::cout << "=== Testing Insert Operation ===" << std::endl;
    
    std::cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    tree.insert(50);  // Root
    tree.insert(30);  // Left of root
    tree.insert(70);  // Right of root
    tree.insert(20);  // Left of 30
    tree.insert(40);  // Right of 30
    tree.insert(60);  // Left of 70
    tree.insert(80);  // Right of 70
    
    std::cout << "BST after insertions (inorder): ";
    tree.printInOrder();  // Should print: 20 30 40 50 60 70 80
    
    std::cout << "Inserting duplicate value 50: " 
              << (tree.insert(50) ? "Success" : "Failed as expected") << std::endl;
}

void testErase(BST& tree) {
    std::cout << "\n=== Testing Erase Operation ===" << std::endl;
    
    // Case 1: Delete a leaf node
    std::cout << "Deleting leaf node (20): " 
              << (tree.erase(20) ? "Success" : "Failed") << std::endl;
    std::cout << "BST after deleting 20: ";
    tree.printInOrder();  // Should print: 30 40 50 60 70 80
    
    // Case 2: Delete a node with one child
    std::cout << "Inserting 25..." << std::endl;
    tree.insert(25);
    std::cout << "BST after inserting 25: ";
    tree.printInOrder();  // Should print: 25 30 40 50 60 70 80
    
    std::cout << "Deleting node with one child (30): " 
              << (tree.erase(30) ? "Success" : "Failed") << std::endl;
    std::cout << "BST after deleting 30: ";
    tree.printInOrder();  // Should print: 25 40 50 60 70 80
    
    // Case 3: Delete a node with two children
    std::cout << "Deleting node with two children (50): " 
              << (tree.erase(50) ? "Success" : "Failed") << std::endl;
    std::cout << "BST after deleting 50 (root): ";
    tree.printInOrder();  // Should show the new structure
    
    // Case 4: Delete non-existing value
    std::cout << "Deleting non-existing value (100): " 
              << (tree.erase(100) ? "Success" : "Failed as expected") << std::endl;
}

void testComplexScenario() {
    std::cout << "\n=== Testing More Complex Scenario ===" << std::endl;
    BST tree;
    
    // Insert in a specific order to test balancing
    int values[] = {15, 10, 20, 8, 12, 17, 25, 6, 11, 16, 27};
    std::cout << "Inserting values: ";
    for (int val : values) {
        std::cout << val << " ";
        tree.insert(val);
    }
    std::cout << std::endl;
    
    std::cout << "BST after insertions (inorder): ";
    tree.printInOrder();
    
    // Delete values in specific order
    int deleteValues[] = {8, 20, 15, 25};
    for (int val : deleteValues) {
        std::cout << "Deleting " << val << ": " << (tree.erase(val) ? "Success" : "Failed") << std::endl;
        std::cout << "BST after deletion: ";
        tree.printInOrder();
    }
}

int main() {
    std::cout << "Binary Search Tree Test Program\n" << std::endl;
    
    // Test 1: Basic Insert and Traversal
    BST bst;
    testInsert(bst);
    
    // Test 2: Various Delete Scenarios
    testErase(bst);
    
    // Test 3: More Complex Scenario
    testComplexScenario();
    
    std::cout << "\nAll tests completed!" << std::endl;
    return 0;
}