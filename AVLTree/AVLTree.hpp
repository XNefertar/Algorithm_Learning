#pragma once
#include <cassert>
#include <iostream>

struct TreeNode {
    int _key;
    TreeNode* _left;
    TreeNode* _right;
    TreeNode* _parent;

    int _balanceFactor;

    TreeNode(int key) : _key(key), _left(nullptr), _right(nullptr), _parent(nullptr), _balanceFactor(0) {}
};

class AVLTree {
private:
    TreeNode* _root;

public:
    AVLTree() : _root(nullptr) {}
	~AVLTree() {
		// Destructor to clean up the tree
		// Implement a proper destructor to delete all nodes
	}

private:
    // Left Rotate
    void leftRotate(TreeNode* parent) {
        TreeNode* subRight = parent->_right;
        TreeNode* subRightLeft = subRight->_left;
        TreeNode* grandParent = parent->_parent;

        parent->_right = subRightLeft;

        if (subRightLeft) {
            subRightLeft->_parent = parent;
        }

        subRight->_left = parent;
        parent->_parent = subRight;

        subRight->_parent = grandParent;

        if (grandParent == nullptr) {
            _root = subRight;
            _root->_parent = nullptr;
        }
        else {
            if (grandParent->_key > subRight->_key) {
                grandParent->_left = subRight;
            }
            else {
                grandParent->_right = subRight;
            }
        }
        parent->_balanceFactor = subRight->_balanceFactor = 0;
    }

    // Right Rotate
    void rightRotate(TreeNode* parent) {
        TreeNode* subLeft = parent->_left;
        TreeNode* subLeftRight = subLeft->_right;
        TreeNode* grandParent = parent->_parent;

        parent->_left = subLeftRight;

        if (subLeftRight) {
            subLeftRight->_parent = parent;
        }
        subLeft->_right = parent;
        parent->_parent = subLeft;

        subLeft->_parent = grandParent;

        if (grandParent == nullptr) {
            _root = subLeft;
            _root->_parent = nullptr;
        }
        else {
            if (grandParent->_key > subLeft->_key) {
                grandParent->_left = subLeft;
            }
            else {
                grandParent->_right = subLeft;
            }
        }
        parent->_balanceFactor = subLeft->_balanceFactor = 0;
    }

    // Left + Right Rotate
    void leftRightRotate(TreeNode* parent) {
        TreeNode* subLeft = parent->_left;
        TreeNode* subLeftRight = subLeft->_right;
        int balanceFactor = subLeftRight->_balanceFactor;

        leftRotate(subLeft);
        rightRotate(parent);
        // renew balance factor
        if (balanceFactor == -1) {
            subLeft->_balanceFactor = 0;
            parent->_balanceFactor = 1;
            subLeftRight->_balanceFactor = 0;
        }
        else if (balanceFactor == 1) {
            subLeft->_balanceFactor = -1;
            parent->_balanceFactor = 0;
            subLeftRight->_balanceFactor = 0;
        }
        else if (balanceFactor == 0) {
            subLeft->_balanceFactor = 0;
            parent->_balanceFactor = 0;
            subLeftRight->_balanceFactor = 0;
        }
    }

    // Right + Left Rotate
    void rightLeftRotate(TreeNode* parent) {
        TreeNode* subRight = parent->_right;
        TreeNode* subRightLeft = subRight->_left;
        int balanceFactor = subRightLeft->_balanceFactor;

        rightRotate(subRight);
        leftRotate(parent);
        if (balanceFactor == -1) {
            subRight->_balanceFactor = 1;
            parent->_balanceFactor = 0;
            subRightLeft->_balanceFactor = 0;

        }
        else if (balanceFactor == 1) {
            subRight->_balanceFactor = 0;
            parent->_balanceFactor = -1;
            subRightLeft->_balanceFactor = 0;

        }
        else if (balanceFactor == 0) {
            subRight->_balanceFactor = 0;
            parent->_balanceFactor = 0;
            subRightLeft->_balanceFactor = 0;
        }
    }

private:
    bool isBalanced(TreeNode* node) {
        if (node == nullptr) {
            return true;
        }

        int leftHeight = getHeight(node->_left);
        int rightHeight = getHeight(node->_right);

        if (rightHeight - rightHeight != node->_balanceFactor) {
            std::cerr << "Exception Balance Factor..." << std::endl;
            return false;
        }

        return (abs(rightHeight - leftHeight) <= 1) && isBalanced(node->_left) && isBalanced(node->_right);
    }

    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getHeight(node->_left);
        int rightHeight = getHeight(node->_right);

        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

    void printInorder(TreeNode* node) {
        if (node == nullptr) return;
        printInorder(node->_left);
        std::cout << node->_key << ' ';
        printInorder(node->_right);
    }

public:
    int getHeight() {
        return getHeight(_root);
    }

    bool isBalanced() {
        return isBalanced(_root);
    }

    void printInorder() {
        printInorder(_root);
    }

public:
    bool insertNode(int key) {
        if (_root == nullptr) {
            _root = new TreeNode(key);
            return true;
        }

        // Find the position to insert
        TreeNode* parent = nullptr;
        TreeNode* cur = _root;
        while (cur) {
            if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            }
            else if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            }
            else {
                return false;
            }
        }

        // insert operation
        cur = new TreeNode(key);
        if (parent->_key > key) {
            parent->_left = cur;
            cur->_parent = parent;
        }
        else {
            parent->_right = cur;
            cur->_parent = parent;
        }

        // renew balance factor
        while (parent) {
            if (parent->_left == cur) {
                parent->_balanceFactor--;
            }
            else {
                parent->_balanceFactor++;
            }

            if (parent->_balanceFactor == 0) {

            }
            else if (parent->_balanceFactor == 1 || parent->_balanceFactor == -1) {
                cur = parent;
                parent = parent->_parent;
            }
            else {
                // Rotate
                if (parent->_balanceFactor == 2 && cur->_balanceFactor == 1) {
                    leftRotate(parent);
                }
                else if (parent->_balanceFactor == -2 && cur->_balanceFactor == -1) {
                    rightRotate(parent);
                }
                else if (parent->_balanceFactor == 2 && cur->_balanceFactor == -1) {
                    rightLeftRotate(parent);
                }
                else if (parent->_balanceFactor == -2 && cur->_balanceFactor == 1) {
                    leftRightRotate(parent);
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }

};
