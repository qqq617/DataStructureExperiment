#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
template <typename T>
struct TreeNode
{
    T data;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(const T &value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
void preorder(const TreeNode<T> *root)
{
    if (root == nullptr)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

template <typename T>
void inorder(const TreeNode<T> *root)
{
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

template <typename T>
void posorder(const TreeNode<T> *root)
{
    if (root == nullptr)
        return;

    posorder(root->left);
    posorder(root->right);
    cout << root->data << " ";
}

template <typename T>
void levelorder(const TreeNode<T> *root)
{
    if (root == nullptr)
        return;

    queue<const TreeNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        const TreeNode<T> *cur = q.front();
        q.pop();
        cout << cur->data << " ";

        if (cur->left != nullptr)
            q.push(cur->left);
        if (cur->right != nullptr)
            q.push(cur->right);
    }
}

template <typename T>
int countNodes(const TreeNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

template <typename T>
int countHeight(const TreeNode<T> *root)
{
    if (root == nullptr)
        return 0;

    return 1 + max(countHeight(root->left), countHeight(root->right));
}

template <typename T>
int countLeaves(const TreeNode<T> *root)
{
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

template <typename T>
TreeNode<T> *findNode(TreeNode<T> *root, const T &target)
{
    if (root == nullptr)
        return nullptr;

    if (root->data == target)
        return root;

    TreeNode<T> *p = findNode(root->left, target);
    if (p != nullptr)
        return p;

    return findNode(root->right, target);
}

template <typename T>
void destroyTree(TreeNode<T> *&root)
{
    if (root == nullptr)
        return;

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = nullptr;
}