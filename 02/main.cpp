
#include <iostream>
#include <vector>

bool maze_solver(const std::vector<std::vector<int>>& maze);

int main() {
    int rows, cols;

    std::cout << "Enter the maze size (rows cols): ";
    std::cin >> rows >> cols;

    if (rows <= 0 || cols <= 0) {
        std::cerr << "Invalid maze size!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> maze(
        rows, std::vector<int>(cols)
    );

    std::cout << "Enter the maze (0: path, 1: wall):"
              << std::endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> maze[i][j];
        }
    }

    if (maze_solver(maze)) {
        std::cout << "Path found!" << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }

    return 0;
}
