#include "ColumnMatrix.h"
#include "RandomNumberGenerator.h"
#include "RectangularMatrix.h"
#include "RowMatrix.h"
#include <iostream>
size_t ColumnMatrix::numRows() const {
    return data.size();
}

size_t ColumnMatrix::numCols() const {
    return 1;
}

ColumnMatrix::ColumnMatrix(int rows) {
    data.resize(rows, std::vector<int>(1));
    RandomNumberGenerator* rng = RandomNumberGenerator::getInstance();
    for (auto& row : data) {
        row[0] = rng->getRandomNumber() % 100;
    }
}

void ColumnMatrix::display() {
    for (const auto& row : data) {
        std::cout << row[0] << std::endl;
    }
}
std::unique_ptr<Matrix> ColumnMatrix::add(const Matrix& other) const {
    // Check dimensions match
    if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    // Perform addition
    auto result = std::make_unique<ColumnMatrix>(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            result->data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}
std::unique_ptr<Matrix> ColumnMatrix::subtract(const Matrix& other) const {
    const auto& otherColumnMatrix = dynamic_cast<const ColumnMatrix&>(other);

    if (data.size() != otherColumnMatrix.data.size() || data[0].size() != otherColumnMatrix.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    auto result = std::make_unique<ColumnMatrix>(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result->data[i][0] = data[i][0] - otherColumnMatrix.data[i][0];
    }
    return result;
}

std::unique_ptr<Matrix> ColumnMatrix::multiply(const Matrix& other) const {
    const auto& otherMatrix = dynamic_cast<const RowMatrix&>(other);

    if (data.size() != otherMatrix.data[0].size()) {
        throw std::invalid_argument("Invalid dimensions for matrix multiplication.");
    }

    int n = data.size();
    int m = otherMatrix.data[0].size();
    auto result = std::make_unique<RectangularMatrix>(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result->data[i][j] = data[i][0] * otherMatrix.data[0][j];
        }
    }
    return result;
}
std::unique_ptr<Matrix> ColumnMatrix::multiplyRecursive(const Matrix& other) const {
    throw std::runtime_error("Recursive multiplication not supported for this matrix type.");
}
std::unique_ptr<Matrix> ColumnMatrix::scalarMultiply(int scalar) const {
    auto result = std::make_unique<ColumnMatrix>(this->numRows());
    for (size_t i = 0; i < this->numRows(); ++i) {
        result->data[i][0] = this->data[i][0] * scalar;
    }
    return result;
}
std::unique_ptr<Matrix> ColumnMatrix::transpose() const {
    auto result = std::make_unique<RowMatrix>(this->numRows());
    for (size_t i = 0; i < this->numRows(); ++i) {
        result->data[0][i] = this->data[i][0];
    }
    return result;
}