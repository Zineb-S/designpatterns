#include "RectangularMatrix.h"
#include "RandomNumberGenerator.h"
#include <iostream>
size_t RectangularMatrix::numRows() const {
    return data.size();
}

size_t RectangularMatrix::numCols() const {
    return data[0].size();
}

RectangularMatrix::RectangularMatrix(int rows, int columns) {
    data.resize(rows, std::vector<int>(columns));
    RandomNumberGenerator* rng = RandomNumberGenerator::getInstance();
    for (auto& row : data) {
        for (int& val : row) {
            val = rng->getRandomNumber() % 100;
        }
    }
}

void RectangularMatrix::display() {
    for (const auto& row : data) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}
std::unique_ptr<Matrix> RectangularMatrix::add(const Matrix& other) const {
    // Dynamic cast to check if 'other' is of type RectangularMatrix
    const auto& otherRectMatrix = dynamic_cast<const RectangularMatrix&>(other);

    if (data.size() != otherRectMatrix.data.size() || data[0].size() != otherRectMatrix.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    auto result = std::make_unique<RectangularMatrix>(data.size(), data[0].size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            result->data[i][j] = data[i][j] + otherRectMatrix.data[i][j];
        }
    }
    return result;
}

std::unique_ptr<Matrix> RectangularMatrix::subtract(const Matrix& other) const {
    const auto& otherRectMatrix = dynamic_cast<const RectangularMatrix&>(other);

    if (data.size() != otherRectMatrix.data.size() || data[0].size() != otherRectMatrix.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    auto result = std::make_unique<RectangularMatrix>(data.size(), data[0].size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            result->data[i][j] = data[i][j] - otherRectMatrix.data[i][j];
        }
    }
    return result;
}

std::unique_ptr<Matrix> RectangularMatrix::multiply(const Matrix& other) const {
    const auto& otherMatrix = dynamic_cast<const RectangularMatrix&>(other);

    if (data[0].size() != otherMatrix.data.size()) {
        throw std::invalid_argument("Invalid dimensions for matrix multiplication.");
    }

    int n = data.size();
    int p = data[0].size();
    int m = otherMatrix.data[0].size();
    auto result = std::make_unique<RectangularMatrix>(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result->data[i][j] = 0;
            for (int k = 0; k < p; ++k) {
                result->data[i][j] += data[i][k] * otherMatrix.data[k][j];
            }
        }
    }
    return result;
}
std::unique_ptr<Matrix> RectangularMatrix::multiplyRecursive(const Matrix& other) const {
    throw std::runtime_error("Recursive multiplication not supported for this matrix type.");
}
std::unique_ptr<Matrix> RectangularMatrix::scalarMultiply(int scalar) const {
    auto result = std::make_unique<RectangularMatrix>(this->numRows(), this->numCols());
    for (size_t i = 0; i < this->numRows(); ++i) {
        for (size_t j = 0; j < this->numCols(); ++j) {
            result->data[i][j] = this->data[i][j] * scalar;
        }
    }
    return result;
}
std::unique_ptr<Matrix> RectangularMatrix::transpose() const {
    auto result = std::make_unique<RectangularMatrix>(this->numCols(), this->numRows());
    for (size_t i = 0; i < this->numRows(); ++i) {
        for (size_t j = 0; j < this->numCols(); ++j) {
            result->data[j][i] = this->data[i][j];
        }
    }
    return result;
}
