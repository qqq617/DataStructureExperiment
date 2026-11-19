#include "BinaryTree.hpp"
#include <iostream>
using namespace std;
int main() {
    /* 构建如下二叉树：
            1
           / \
          2   3
         / \   \
        4   5   6
    */
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(6);

    // 调用你修正后的前序遍历（预期输出: 1 2 4 5 3 6）
    // preorder_iter(root);
    preorder(root);
    cout << endl;
    preorder_r(root);
    cout << endl;
    inorder(root);
    cout << endl;
    inorder_r(root);
    cout << endl;
    posorder(root);
    cout << endl;
    posorder_r(root);

    destroyTree(root); // 释放内存
    return 0;
}