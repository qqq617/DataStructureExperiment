#include "sparse_matrix.h"
#include <iostream>

int main() {
    try {
        long long rows, cols, entries;
        if (!(std::cin >> rows >> cols >> entries) || rows < 0 || cols < 0 || entries < 0)
            throw std::invalid_argument("expected nonnegative rows, columns and entry count");
        SparseMatrix matrix(static_cast<std::size_t>(rows), static_cast<std::size_t>(cols));
        for (long long i = 0; i < entries; ++i) {
            long long row, col;
            std::int64_t value;
            if (!(std::cin >> row >> col >> value) || row < 0 || col < 0)
                throw std::invalid_argument("expected row column value with nonnegative indices");
            matrix.set(static_cast<std::size_t>(row), static_cast<std::size_t>(col), value);
        }
        std::cout << "Original matrix (row column value):\n";
        matrix.print(std::cout);
        matrix.transpose();
        std::cout << "Transposed matrix (row column value):\n";
        matrix.print(std::cout);
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
