#pragma once
#include <iostream>
enum Color {
    BLACK = 0,
    RED
};

struct TreeNode {
    int _color;
    int _value;
    TreeNode* _left;
    TreeNode* _right;
    TreeNode* _parent;

    TreeNode(int value) : _value(value), _left(nullptr), _right(nullptr), _parent(nullptr), _color(RED) {}
};

class RBTree {
private:
    TreeNode* _root;
private:
    void rightRotate(TreeNode* node) {
        TreeNode* subLeft = node->_left;
        TreeNode* subLeftRight = subLeft->_right;
        if (subLeftRight) {
            subLeftRight->_parent = node;
        }
        node->_left = subLeftRight;

        TreeNode* grandParent = node->_parent;
        subLeft->_parent = grandParent;

        if (grandParent == nullptr) {
            _root = subLeft;
            _root->_parent = nullptr;
        }
        else if (grandParent->_left == node) {
            grandParent->_left = subLeft;
        }
        else {
            grandParent->_right = subLeft;
        }
		subLeft->_parent = grandParent;
        subLeft->_right = node;
        node->_parent = subLeft;
    }
    void leftRotate(TreeNode* node) {
        TreeNode* subRight = node->_right;
        TreeNode* subRightLeft = subRight->_left;
        if (subRightLeft) {
            subRightLeft->_parent = node;
        }
        node->_right = subRightLeft;

        TreeNode* grandParent = node->_parent;
        if (grandParent == nullptr) {
            _root = subRight;
            _root->_parent = nullptr;
        }
        else if (grandParent->_left == node) {
            grandParent->_left = subRight;
        }
        else if (grandParent->_right == node) {
            grandParent->_right = subRight;
        }
		subRight->_parent = grandParent;
        subRight->_left = node;
        node->_parent = subRight;
    }
    void inOrderTraversal(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }
        inOrderTraversal(node->_left);
        std::cout << "Value: " << node->_value << ", Color: " << (node->_color == RED ? "RED" : "BLACK") << std::endl;
        inOrderTraversal(node->_right);
    }

public:
    void printInOrder() const {
        inOrderTraversal(_root);
    }

    TreeNode* getTreeRoot() {
        // This is a workaround since _root is private
        // You might want to add a public getRoot() method instead
        return _root;
    }

public:
    RBTree() :_root(nullptr) {}
    ~RBTree() {}

public:
    bool insertNode(int value) {
        if (_root == nullptr) {
            _root = new TreeNode(value);
            _root->_color = BLACK;
            return true;
        }

        TreeNode* cur = _root;
        TreeNode* parent = nullptr;
        while (cur) {
            if (cur->_value > value) {
                parent = cur;
                cur = cur->_left;
            }
            else if (cur->_value < value) {
                parent = cur;
                cur = cur->_right;
            }
            else {
                return false;
            }
        }

        cur = new TreeNode(value);
        if (parent->_value > value) {
            parent->_left = cur;
            cur->_parent = parent;
        }
        else {
            parent->_right = cur;
            cur->_parent = parent;
        }

        while (parent && parent->_color == RED) {
            // find the uncle point
            TreeNode* grandParent = parent->_parent;
            TreeNode* unclePoint = nullptr;
            if (grandParent->_left == parent) {
                unclePoint = grandParent->_right;
                if (unclePoint && unclePoint->_color == RED) {
                    parent->_color = unclePoint->_color = BLACK;
                    grandParent->_color = RED;
                    cur = grandParent;
                    parent = cur->_parent;
                }
                else {
                    if (parent->_left == cur) {
                        rightRotate(grandParent);
                        parent->_color = BLACK;
                        grandParent->_color = RED;
                    }
                    else {
                        leftRotate(parent);
                        rightRotate(grandParent);
                        cur->_color = BLACK;
                        grandParent->_color = parent->_color = RED;
                    }
                    break;
                }
            }
            else {
                unclePoint = grandParent->_left;

                if (unclePoint && unclePoint->_color == RED) {
                    parent->_color = unclePoint->_color = BLACK;
                    grandParent->_color = RED;
                    cur = grandParent;
                    parent = cur->_parent;
                }
                else {
                    if (parent->_right == cur) {
                        leftRotate(grandParent);
                        parent->_color = BLACK;
                        grandParent->_color = RED;
                    }
                    else {
                        rightRotate(parent);
                        leftRotate(grandParent);
                        cur->_color = BLACK;
                        grandParent->_color = parent->_color = RED;
                    }
                    break;
                }
            }
        }
        if (_root) {
            _root->_color = BLACK;
        }

        return true;
    }
};
