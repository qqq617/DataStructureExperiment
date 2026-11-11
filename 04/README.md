# Data Structure Experiment 4

## Tasks

1. Implement sparse matrix with Orthogonal List. ✓
2. Implement the transpose of sparse matrices. ✓

## Development Environment

- WSL2 (Ubuntu)
- G++ (C++ compiler)
- Visual Studio Code
- Git

## 编译与运行

```bash
make
./sparse_matrix
make test
```

也可以直接编译：`g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o sparse_matrix`。

输入第一行为 `行数 列数 输入项数`，之后每行为 `行号 列号 整数值`，下标从 **0** 开始。重复坐标覆盖原值，赋值为 0 时删除该元素。支持空矩阵；负数维度、非法下标和不完整输入会报错并返回非零退出码。

例如输入：

```text
3 4 4
0 1 5
1 3 8
2 0 -2
2 2 6
```

输出：

```text
Original matrix (row column value):
3 4 4
0 1 5
1 3 8
2 0 -2
2 2 6
Transposed matrix (row column value):
4 3 4
0 2 -2
1 0 5
2 2 6
3 1 8
```

## 实现说明

`sparse_matrix.h` 中的 `SparseMatrix` 使用十字链表存储非零元素：每个结点记录行、列、值，`right` 指向同行的下一非零元素，`down` 指向同列的下一非零元素。行链按列号升序，列链按行号升序；两组头指针分别管理所有行和列。元素值为 64 位有符号整数。

- `set(row, col, value)`：插入、修改或删除元素，同时维护行链和列链。
- `get(row, col)`：查询元素，未存储的元素返回 0。
- `transpose()`：原地交换每个结点的行列号及左右两个链接方向（`right` 与 `down`），最后交换行列头指针数组。遍历时先保存原 `right`，保证每个结点只处理一次。
- `clear()` 和析构函数：沿行链释放结点，避免重复释放；复制构造与赋值采用深拷贝。

设矩阵有 m 行、n 列、k 个非零元素，存储空间为 O(m+n+k)。转置时间为 O(m+k)，额外空间为 O(1)。查询耗时为当前行非零元素数的 O(行长度)，插入和删除最坏为 O(行长度+列长度)。

`tests.cpp` 使用固定随机种子与普通二维数组对照，检查插入、覆盖、删除、矩形矩阵转置、二次转置、转置后的修改，以及深拷贝、空矩阵和越界处理。
