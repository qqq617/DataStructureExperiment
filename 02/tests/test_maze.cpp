#include"LinkedStack.hpp"
#include<iostream>
#include<vector>
#include<stdexcept>
#include <cassert>
using namespace std;

bool maze_solver(const vector<vector<int>>& maze);

void testMazeSolver(){
    // 1. 正常迷宫：存在路径
    vector<vector<int>> maze1 = {
        {0, 0, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 0, 0}
    };
    assert(maze_solver(maze1) == true);

    // 2. 不存在路径
    vector<vector<int>> maze2 = {
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 0}
    };
    assert(maze_solver(maze2) == false);

    // 3. 起点是墙壁
    vector<vector<int>> maze3 = {
        {1, 0},
        {0, 0}
    };
    assert(maze_solver(maze3) == false);

    // 4. 终点是墙壁
    vector<vector<int>> maze4 = {
        {0, 0},
        {0, 1}
    };
    assert(maze_solver(maze4) == false);

    // 5. 只有一个可通行格子
    vector<vector<int>> maze5 = {{0}};
    assert(maze_solver(maze5) == true);

    // 6. 只有一个墙壁格子
    vector<vector<int>> maze6 = {{1}};
    assert(maze_solver(maze6) == false);

    // 7. 空迷宫，应抛出异常
    bool caught = false;
    try {
        maze_solver({});
    } catch(const invalid_argument&) {
        caught = true;
    }
    assert(caught);

    // 8. 不规则迷宫，应抛出异常
    caught = false;
    try {
        maze_solver({{0, 0}, {0}});
    } catch(const invalid_argument&) {
        caught = true;
    }
    assert(caught);

    cout << "All maze tests passed!" << endl;
}

int main(){
    testMazeSolver();
    return 0;
}
