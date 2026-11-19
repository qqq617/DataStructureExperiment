# Data Structure Experiment 5

## Tasks

1. Implement a linked binary tree. ✓
2. Implement recursive and iterative preorder, inorder, and postorder traversals. ✓
3. Implement level-order traversal, node and leaf counting, height calculation, node search, and tree cleanup. ✓

## Development Environment

- WSL2 (Ubuntu)
- G++ (C++17)
- CMake 3.15+
- Visual Studio Code
- Git

## 编译与运行

在 `05` 目录下执行以下命令。需要 CMake 3.15 或更高版本，以及支持 C++17 的编译器（如 GCC）。

```bash
cmake -S . -B build
cmake --build build
./build/main
```

程序使用以下示例树，无需输入。

```text
    1
   / \
  2   3
 / \   \
4   5   6
```

程序依次打印前序、中序和后序遍历结果。每种遍历先打印递归版本，再打印迭代版本。

```text
1 2 4 5 3 6
1 2 4 5 3 6
4 2 5 1 3 6
4 2 5 1 3 6
4 5 2 6 3 1
4 5 2 6 3 1
```

## 实现说明

`BinaryTree.hpp` 中的 `TreeNode<T>` 保存结点数据和左右孩子指针，创建结点时两个孩子指针均初始化为空。`main.cpp` 构建示例树并演示遍历，最后释放整棵树。

| 操作 | 函数 | 实现方式 |
| --- | --- | --- |
| 前序遍历 | `preorder`、`preorder_r` | 按根、左、右的顺序访问。迭代版先压入右孩子，再压入左孩子。 |
| 中序遍历 | `inorder`、`inorder_r` | 按左、根、右的顺序访问。迭代版沿左链入栈，出栈访问后转向右子树。 |
| 后序遍历 | `posorder`、`posorder_r` | 按左、右、根的顺序访问。迭代版用栈和最近访问的结点判断右子树是否已处理。 |
| 层序遍历 | `levelorder` | 用队列逐层访问，同层从左到右。 |
| 统计 | `countNodes`、`countHeight`、`countLeaves` | 递归计算结点数、树高和叶子数。空树高度为 0，单结点树高度为 1。 |
| 查找 | `findNode` | 按前序查找第一个匹配的结点，找不到时返回 `nullptr`。 |
| 释放 | `destroyTree` | 按后序释放结点，并将传入的根指针置空。 |

设树有 `n` 个结点、高度为 `h`、最大层宽为 `w`。四种遍历的时间复杂度均为 `O(n)`。前序、中序和后序遍历的额外空间为 `O(h)`，层序遍历的额外空间为 `O(w)`。
