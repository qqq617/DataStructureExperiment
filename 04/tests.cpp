#include "sparse_matrix.h"
#include <cassert>
#include <random>
#include <sstream>

int main() {
    SparseMatrix matrix(7, 11);
    std::vector<std::vector<std::int64_t>> dense(7, std::vector<std::int64_t>(11));
    std::mt19937 rng(42);
    for (int step = 0; step < 1000; ++step) {
        const auto row = rng() % 7, col = rng() % 11;
        const auto value = static_cast<int>(rng() % 9) - 4;
        matrix.set(row, col, value);
        dense[row][col] = value;
        std::size_t count = 0;
        for (std::size_t r = 0; r < 7; ++r)
            for (std::size_t c = 0; c < 11; ++c) {
                assert(matrix.get(r, c) == dense[r][c]);
                count += dense[r][c] != 0;
            }
        assert(matrix.nonzeros() == count);
        matrix.transpose();
        assert(matrix.rows() == 11 && matrix.cols() == 7);
        for (std::size_t r = 0; r < 7; ++r)
            for (std::size_t c = 0; c < 11; ++c)
                assert(matrix.get(c, r) == dense[r][c]);
        // Exercise insertion/removal using the transposed column links too.
        matrix.set(col, row, 0);
        matrix.set(col, row, value);
        matrix.transpose();
    }
    SparseMatrix copy(matrix);
    std::ostringstream a, b;
    matrix.print(a);
    copy.print(b);
    assert(a.str() == b.str());
    copy.clear();
    assert(copy.nonzeros() == 0 && matrix.nonzeros() != 0);
    copy = matrix;
    copy = copy;
    assert(copy.nonzeros() == matrix.nonzeros());
    bool rejected = false;
    try { matrix.set(7, 0, 1); }
    catch (const std::out_of_range&) { rejected = true; }
    assert(rejected);
    for (auto dimensions : {std::pair<std::size_t, std::size_t>{0, 0}, {0, 5}, {5, 0}, {3, 4}}) {
        SparseMatrix empty(dimensions.first, dimensions.second);
        empty.transpose();
        assert(empty.rows() == dimensions.second && empty.cols() == dimensions.first);
        assert(empty.nonzeros() == 0);
    }
}
