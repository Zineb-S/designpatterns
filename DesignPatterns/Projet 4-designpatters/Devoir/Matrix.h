#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <memory>

class Matrix {
public:
    virtual void display() = 0;
    virtual size_t numRows() const = 0;
    virtual size_t numCols() const = 0;
    virtual std::unique_ptr<Matrix> add(const Matrix& other) const = 0;
    virtual std::unique_ptr<Matrix> subtract(const Matrix& other) const = 0;
    virtual std::unique_ptr<Matrix> multiply(const Matrix& other) const = 0;
    virtual std::unique_ptr<Matrix> multiplyRecursive(const Matrix &other) const = 0;
    virtual std::unique_ptr<Matrix> scalarMultiply(int scalar) const = 0;
    virtual std::unique_ptr<Matrix> transpose() const = 0;

    virtual int getElement(size_t row, size_t col) const = 0;
    virtual void setElement(size_t row, size_t col, int value) = 0;

    virtual ~Matrix() {}
    std::vector<std::vector<int>> data;
};

#endif // MATRIX_H
