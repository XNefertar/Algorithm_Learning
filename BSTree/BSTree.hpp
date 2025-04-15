#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, * right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;
public:
    BST() : root(nullptr) {}

    bool insert(int val) {
        TreeNode* cur = root, * parent = nullptr;

        while (cur) {
            parent = cur;
            if (val < cur->val)
                cur = cur->left;
            else if (val > cur->val)
                cur = cur->right;
            else
                return false; // 重复值，不插入
        }

        TreeNode* newNode = new TreeNode(val);
        if (!parent) {
            // 说明树为空
            root = newNode;
        }
        else if (val < parent->val) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
        return true;
    }

    bool erase(int val) {
        TreeNode* cur = root, * pre_parent = nullptr;

        while (cur) {
            pre_parent = cur;
            if (val < cur->val) {
                cur = cur->left;
            }
            else if (val > cur->val) {
                cur = cur->right;
            }
            else break;
        }

        if (!cur) return false; // 没找到
        // left == nullptr
        if (cur->left == nullptr) {
            if (pre_parent == nullptr) {
                root = cur->right;
            } else if (pre_parent->left == cur) {
                pre_parent->left = cur->right;
            } else {
                pre_parent->right = cur->right;
            }
        }
        else if (cur->right == nullptr) {
            if (pre_parent == nullptr) {
                root = cur->left;
            } else if (pre_parent->left == cur) {
                pre_parent->left = cur->left;
            } else {
                pre_parent->right = cur->left;
            }
        }
        else {
            TreeNode* leftMax = cur->left, * parent = cur;
            while (leftMax->right) {
                parent = leftMax;
                leftMax = leftMax->right;
            }
            cur->val = leftMax->val;
            if (parent == cur) {
                parent->left = leftMax->left;
            } else {
                parent->right = leftMax->left;
            }
            delete leftMax;

        }
        return true;
    }

    void inorderTraversal(TreeNode* node) {
        if (!node) return;
        inorderTraversal(node->left);
        cout << node->val << " ";
        inorderTraversal(node->right);
    }

    void printInOrder() {
        inorderTraversal(root);
        cout << endl;
    }

};