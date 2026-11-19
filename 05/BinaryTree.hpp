#include <iostream>
#include <stack>
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
void preorder_r(const TreeNode<T> *root){
    if (root == nullptr) return;
    stack<const TreeNode<T>*> s;
    s.push(root);
    while (!s.empty()){
        const TreeNode<T>* cur = s.top();
        cout << cur->data <<" ";
        s.pop();
        if (cur->right != nullptr) s.push(cur->right);
        if (cur->left != nullptr) s.push(cur->left);
    }
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
void inorder_r(const TreeNode<T> *root){
    if (root == nullptr) return;

    stack<const TreeNode<T>*> s;
    const TreeNode<T>* cur = root;
    while (!s.empty() || cur != nullptr) {

        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();
        cout << cur->data <<" ";

        cur = cur->right;
    }
    // int debug_steps = 0;
    // while (!s.empty()) {
    //     if (++debug_steps > 20) { // 超过树的总节点数就强行熔断
    //     std::cout << "\n[ERROR] 触发死循环熔断！\n";
    //     break;
    //     }
    //     const TreeNode<T>* cur = s.top();
    //     s.pop();
    //     if (cur->right != nullptr) s.push(cur->right);
    //     s.push(cur);
    //     if (cur->left != nullptr) {
    //         s.push(cur->left);
    //     }else {
    //         cout << cur->data <<" ";
    //         s.pop();
    //         cur = s.top();
    //         cout << cur->data <<" ";
    //         s.pop();
    //     }
    // }
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
void posorder_r(const TreeNode<T> *root){
    if (root == nullptr) return;
    stack<const TreeNode<T>*> s;
    const TreeNode<T>* cur = root;
    const TreeNode<T>* prev = nullptr;
    while (!s.empty() || cur != nullptr) {
        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        if (cur->right != nullptr && cur->right != prev) {
            cur = cur->right;
            continue;
        }
        prev = cur;

        cout << cur->data << " ";

        s.pop();

        cur = nullptr;
    }
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