#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

// Each nonzero node belongs to both a sorted row and a sorted column.
class SparseMatrix {
    struct Node {
        std::size_t row, col;
        std::int64_t value;
        Node *right = nullptr, *down = nullptr;
    };

    std::vector<Node*> rows_, cols_;
    std::size_t count_ = 0;

    void check(std::size_t row, std::size_t col) const {
        if (row >= rows_.size() || col >= cols_.size())
            throw std::out_of_range("matrix index out of range");
    }

public:
    SparseMatrix(std::size_t rows, std::size_t cols)
        : rows_(rows, nullptr), cols_(cols, nullptr) {}

    SparseMatrix(const SparseMatrix& other)
        : SparseMatrix(other.rows(), other.cols()) {
        try {
            for (Node* head : other.rows_)
                for (Node* node = head; node; node = node->right)
                    set(node->row, node->col, node->value);
        } catch (...) {
            clear();
            throw;
        }
    }

    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this != &other) {
            SparseMatrix copy(other);
            swap(copy);
        }
        return *this;
    }

    ~SparseMatrix() { clear(); }

    void swap(SparseMatrix& other) noexcept {
        rows_.swap(other.rows_);
        cols_.swap(other.cols_);
        std::swap(count_, other.count_);
    }

    void clear() noexcept {
        for (Node*& head : rows_) {
            while (head) {
                Node* next = head->right;
                delete head;
                head = next;
            }
        }
        for (Node*& head : cols_) head = nullptr;
        count_ = 0;
    }

    std::size_t rows() const noexcept { return rows_.size(); }
    std::size_t cols() const noexcept { return cols_.size(); }
    std::size_t nonzeros() const noexcept { return count_; }

    std::int64_t get(std::size_t row, std::size_t col) const {
        check(row, col);
        Node* node = rows_[row];
        while (node && node->col < col) node = node->right;
        return node && node->col == col ? node->value : 0;
    }

    // Assigning zero removes a node; repeated coordinates replace its value.
    void set(std::size_t row, std::size_t col, std::int64_t value) {
        check(row, col);
        Node** horizontal = &rows_[row];
        while (*horizontal && (*horizontal)->col < col)
            horizontal = &(*horizontal)->right;
        if (*horizontal && (*horizontal)->col == col) {
            Node* node = *horizontal;
            if (value != 0) {
                node->value = value;
                return;
            }
            Node** vertical = &cols_[col];
            while (*vertical != node) vertical = &(*vertical)->down;
            *horizontal = node->right;
            *vertical = node->down;
            delete node;
            --count_;
        } else if (value != 0) {
            Node** vertical = &cols_[col];
            while (*vertical && (*vertical)->row < row)
                vertical = &(*vertical)->down;
            Node* node = new Node{row, col, value, *horizontal, *vertical};
            *horizontal = *vertical = node;
            ++count_;
        }
    }

    // Old down links become new right links. Save old right before swapping.
    void transpose() noexcept {
        for (Node* head : rows_) {
            for (Node* node = head; node;) {
                Node* next = node->right;
                std::swap(node->row, node->col);
                std::swap(node->right, node->down);
                node = next;
            }
        }
        rows_.swap(cols_);
    }

    void print(std::ostream& out) const {
        out << rows() << ' ' << cols() << ' ' << nonzeros() << '\n';
        for (Node* head : rows_)
            for (Node* node = head; node; node = node->right)
                out << node->row << ' ' << node->col << ' ' << node->value << '\n';
    }
};
