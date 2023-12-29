#include "SquareMatrix.h"
#include "RandomNumberGenerator.h"
#include <iostream>
#include <memory>
#include <stdexcept>
size_t SquareMatrix::numRows() const {
    return data.size();
}

size_t SquareMatrix::numCols() const {
    return data.size();
}

SquareMatrix::SquareMatrix(int size) {
    data.resize(size, std::vector<double>(size));
    RandomNumberGenerator* rng = RandomNumberGenerator::getInstance();
    for (auto &row : data) {
        for (double &val : row) {
            val = static_cast<double>(rng->getRandomNumber() % 100);
        }
    }
}

SquareMatrix::SquareMatrix(int size, double initialValue) {
    data.resize(size, std::vector<double>(size, initialValue));
}


void SquareMatrix::display() {
    for (const auto &row : data) {
        for (double val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

std::unique_ptr<Matrix> SquareMatrix::add(const Matrix& other) const {
    const auto& otherSquareMatrix = dynamic_cast<const SquareMatrix&>(other);

    if (data.size() != otherSquareMatrix.data.size() || data[0].size() != otherSquareMatrix.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    auto result = std::make_unique<SquareMatrix>(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            result->data[i][j] = data[i][j] + otherSquareMatrix.data[i][j];
        }
    }
    //this->notify("add", *this);
    return result;
}
std::unique_ptr<Matrix> SquareMatrix::subtract(const Matrix& other) const {
    const auto& otherSquareMatrix = dynamic_cast<const SquareMatrix&>(other);

    if (data.size() != otherSquareMatrix.data.size() || data[0].size() != otherSquareMatrix.data[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    auto result = std::make_unique<SquareMatrix>(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            result->data[i][j] = data[i][j] - otherSquareMatrix.data[i][j];
        }
    }
    return result;
}
std::unique_ptr<Matrix> SquareMatrix::multiply(const Matrix& other) const {
    const auto& otherSquareMatrix = dynamic_cast<const SquareMatrix&>(other);

    if (data[0].size() != otherSquareMatrix.data.size()) {
        throw std::invalid_argument("Invalid dimensions for matrix multiplication.");
    }

    int n = data.size();
    auto result = std::make_unique<SquareMatrix>(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result->data[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                result->data[i][j] += data[i][k] * otherSquareMatrix.data[k][j];
            }
        }
    }
    return result;
}

std::unique_ptr<Matrix> SquareMatrix::multiplyRecursive(const Matrix& other) const {
    const auto& otherSquareMatrix = dynamic_cast<const SquareMatrix&>(other);
    if (data.size() != otherSquareMatrix.data.size()) {
        throw std::invalid_argument("Invalid dimensions for recursive multiplication.");
    }
    return multiplyRecursiveHelper(*this, otherSquareMatrix);
}
/*
std::unique_ptr<SquareMatrix> SquareMatrix::multiplyRecursiveHelper(const SquareMatrix& a, const SquareMatrix& b) {
    size_t n = a.numRows();
    if (n == 1) {
        return std::make_unique<SquareMatrix>(1, a.data[0][0] * b.data[0][0]);
    }

    // Adjust size for non-power of 2 matrices
    size_t newSize = n / 2 + (n % 2);
    SquareMatrix a11(newSize), a12(newSize), a21(newSize), a22(newSize);
    SquareMatrix b11(newSize), b12(newSize), b21(newSize), b22(newSize);

    // Fill submatrices with data
    for (size_t i = 0; i < newSize; i++) {
        for (size_t j = 0; j < newSize; j++) {
            a11.data[i][j] = a.data[i][j];
            a12.data[i][j] = j + newSize < a.numCols() ? a.data[i][j + newSize] : 0;
            a21.data[i][j] = i + newSize < a.numRows() ? a.data[i + newSize][j] : 0;
            a22.data[i][j] = (i + newSize < a.numRows() && j + newSize < a.numCols()) ? a.data[i + newSize][j + newSize] : 0;

            b11.data[i][j] = b.data[i][j];
            b12.data[i][j] = j + newSize < b.numCols() ? b.data[i][j + newSize] : 0;
            b21.data[i][j] = i + newSize < b.numRows() ? b.data[i + newSize][j] : 0;
            b22.data[i][j] = (i + newSize < b.numRows() && j + newSize < b.numCols()) ? b.data[i + newSize][j + newSize] : 0;
        }
    }

    // Recursively multiply submatrices
    auto c11 = multiplyRecursiveHelper(a11, b11)->add(*multiplyRecursiveHelper(a12, b21));
    auto c12 = multiplyRecursiveHelper(a11, b12)->add(*multiplyRecursiveHelper(a12, b22));
    auto c21 = multiplyRecursiveHelper(a21, b11)->add(*multiplyRecursiveHelper(a22, b21));
    auto c22 = multiplyRecursiveHelper(a21, b12)->add(*multiplyRecursiveHelper(a22, b22));

    // Combine submatrices into final result
    auto result = std::make_unique<SquareMatrix>(n);
    for (size_t i = 0; i < newSize; i++) {
        for (size_t j = 0; j < newSize; j++) {
            result->data[i][j] = c11->data[i][j];
            if (j + newSize < result->numCols()) result->data[i][j + newSize] = c12->data[i][j];
            if (i + newSize < result->numRows()) result->data[i + newSize][j] = c21->data[i][j];
            if (i + newSize < result->numRows() && j + newSize < result->numCols()) result->data[i + newSize][j + newSize] = c22->data[i][j];
        }
    }
    return result;
}
*/
std::unique_ptr<SquareMatrix> SquareMatrix::multiplyRecursiveHelper(const SquareMatrix& a, const SquareMatrix& b) {
    size_t n = a.numRows();
    if (n == 1) {
        return std::make_unique<SquareMatrix>(1, a.data[0][0] * b.data[0][0]);
    }

    // Initialize submatrices for A and B matrices
    size_t newSize = n / 2;
    SquareMatrix a11(newSize), a12(newSize), a21(newSize), a22(newSize);
    SquareMatrix b11(newSize), b12(newSize), b21(newSize), b22(newSize);

    // Fill submatrices with data
    for (size_t i = 0; i < newSize; i++) {
        for (size_t j = 0; j < newSize; j++) {
            a11.data[i][j] = a.data[i][j];
            a12.data[i][j] = a.data[i][j + newSize];
            a21.data[i][j] = a.data[i + newSize][j];
            a22.data[i][j] = a.data[i + newSize][j + newSize];

            b11.data[i][j] = b.data[i][j];
            b12.data[i][j] = b.data[i][j + newSize];
            b21.data[i][j] = b.data[i + newSize][j];
            b22.data[i][j] = b.data[i + newSize][j + newSize];
        }
    }
// Continue from the previous code ...

// Recursively multiply submatrices
    auto p1 = multiplyRecursiveHelper(a11, b11);
    auto p2 = multiplyRecursiveHelper(a12, b21);
    auto p3 = multiplyRecursiveHelper(a11, b12);
    auto p4 = multiplyRecursiveHelper(a12, b22);
    auto p5 = multiplyRecursiveHelper(a21, b11);
    auto p6 = multiplyRecursiveHelper(a22, b21);
    auto p7 = multiplyRecursiveHelper(a21, b12);
    auto p8 = multiplyRecursiveHelper(a22, b22);

// Combine submatrices into final result
    auto result = std::make_unique<SquareMatrix>(n);
    for (size_t i = 0; i < newSize; ++i) {
        for (size_t j = 0; j < newSize; ++j) {
            // Combine results for each quadrant of the result matrix
            result->data[i][j] = p1->data[i][j] + p2->data[i][j]; // Top-left
            result->data[i][j + newSize] = p3->data[i][j] + p4->data[i][j]; // Top-right
            result->data[i + newSize][j] = p5->data[i][j] + p6->data[i][j]; // Bottom-left
            result->data[i + newSize][j + newSize] = p7->data[i][j] + p8->data[i][j]; // Bottom-right
        }
    }

    return result;


    return result;
}


std::unique_ptr<Matrix> SquareMatrix::scalarMultiply(int scalar) const {
    auto result = std::make_unique<SquareMatrix>(this->numRows());
    for (size_t i = 0; i < this->numRows(); ++i) {
        for (size_t j = 0; j < this->numCols(); ++j) {
            result->data[i][j] = this->data[i][j] * scalar;
        }
    }
    return result;
}
double SquareMatrix::determinant() const {
    int n = data.size();
    if (n == 1) {
        return data[0][0];
    } else if (n == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    } else {
        double det = 0;
        for (int i = 0; i < n; ++i) {
            SquareMatrix subMatrix = createSubMatrix(0, i);
            det += (i % 2 == 0 ? 1 : -1) * data[0][i] * subMatrix.determinant();
        }
        return det;
    }
}

std::unique_ptr<Matrix> SquareMatrix::inverse() const {
    int n = this->numRows();
    std::cout << "Check if the Matrix is Invertible:" << std::endl;

    double det = this->determinant();
    std::cout << "Compute the Determinant: " << det << std::endl;
    if (det == 0) {
        std::cout << "The matrix is not invertible (determinant is zero)." << std::endl;
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    std::cout << "Compute the Adjugate Matrix:" << std::endl;
    SquareMatrix adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            SquareMatrix subMat = createSubMatrix(i, j);
            double cofactor = sign * subMat.determinant();
            adj.data[j][i] = cofactor;
        }
    }
    adj.display(); // Display the adjugate matrix

    std::cout << "Divide the Adjugate Matrix by the Determinant:" << std::endl;
    auto inverseMat = std::make_unique<SquareMatrix>(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMat->data[i][j] = adj.data[i][j] / det;
        }
    }

    return inverseMat;
}


SquareMatrix SquareMatrix::createSubMatrix(int excludingRow, int excludingColumn) const {
    int n = data.size();
    SquareMatrix subMatrix(n - 1);
    for (int i = 0, row = 0; i < n; ++i) {
        if (i == excludingRow) continue;
        for (int j = 0, col = 0; j < n; ++j) {
            if (j == excludingColumn) continue;
            subMatrix.data[row][col] = data[i][j];
            col++;
        }
        row++;
    }
    return subMatrix;
}

std::unique_ptr<Matrix> SquareMatrix::transpose() const {
    auto result = std::make_unique<SquareMatrix>(this->numRows());
    for (size_t i = 0; i < this->numRows(); ++i) {
        for (size_t j = 0; j < this->numCols(); ++j) {
            result->data[j][i] = this->data[i][j];
        }
    }
    return result;
}
int SquareMatrix::getElement(size_t row, size_t col) const {
    return data[row][col];
}

void SquareMatrix::setElement(size_t row, size_t col, int value) {
    data[row][col] = value;
}
