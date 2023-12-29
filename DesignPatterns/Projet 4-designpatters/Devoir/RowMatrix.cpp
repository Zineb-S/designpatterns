#include "RowMatrix.h"
#include "RandomNumberGenerator.h"
#include "RectangularMatrix.h"
#include "ColumnMatrix.h"
#include <iostream>

size_t RowMatrix::numRows() const {
    return data.size();
}

size_t RowMatrix::numCols() const {
    return data[0].size();
}

RowMatrix::RowMatrix(int columns) {
    data.resize(1, std::vector<int>(columns));
    RandomNumberGenerator* rng = RandomNumberGenerator::getInstance();
    for (int &val : data[0]) {
        val = rng->getRandomNumber() % 100;
    }
}

void RowMatrix::display() {
    for (int val : data[0]) {
        std::cout << val << "\t";
    }
    std::cout << std::endl;
}
std::unique_ptr<Matrix> RowMatrix::add(const Matrix& other) const {
    const auto& otherMatrix = dynamic_cast<const RowMatrix&>(other);
    if (data[0].size() != otherMatrix.data[0].size()) {
        throw std::invalid_argument("Row Matrices must have the same number of columns for addition.");
    }

    auto result = std::make_unique<RowMatrix>(data[0].size());
    for (size_t j = 0; j < data[0].size(); ++j) {
        result->data[0][j] = data[0][j] + otherMatrix.data[0][j];
    }
    return result;
}
std::unique_ptr<Matrix> RowMatrix::subtract(const Matrix& other) const {
    const auto& otherRowMatrix = dynamic_cast<const RowMatrix&>(other);

    if (data.size() != otherRowMatrix.data.size() || data[0].size() != otherRowMatrix.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    auto result = std::make_unique<RowMatrix>(data[0].size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            result->data[i][j] = data[i][j] - otherRowMatrix.data[i][j];
        }
    }
    return result;
}

std::unique_ptr<Matrix> RowMatrix::multiply(const Matrix& other) const {
    if (data[0].size() != other.numRows()) {
        throw std::invalid_argument("Invalid dimensions for matrix multiplication.");
    }

    int m = other.numCols();
    auto result = std::make_unique<RowMatrix>(m);
    for (int j = 0; j < m; ++j) {
        result->data[0][j] = 0;
        for (size_t k = 0; k < data[0].size(); ++k) {
            result->data[0][j] += data[0][k] * other.data[k][j];
        }
    }
    return result;
}
std::unique_ptr<Matrix> RowMatrix::multiplyRecursive(const Matrix& other) const {
    throw std::runtime_error("Recursive multiplication not supported for this matrix type.");
}
std::unique_ptr<Matrix> RowMatrix::scalarMultiply(int scalar) const {
    auto result = std::make_unique<RowMatrix>(this->numCols());
    for (size_t j = 0; j < this->numCols(); ++j) {
        result->data[0][j] = this->data[0][j] * scalar;
    }
    return result;
}
std::unique_ptr<Matrix> RowMatrix::transpose() const {
    auto result = std::make_unique<ColumnMatrix>(this->numCols());
    for (size_t i = 0; i < this->numCols(); ++i) {
        result->data[i][0] = this->data[0][i];
    }
    return result;
}

