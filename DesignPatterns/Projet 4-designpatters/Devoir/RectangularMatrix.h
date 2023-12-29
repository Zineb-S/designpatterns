#ifndef RECTANGULARMATRIX_H
#define RECTANGULARMATRIX_H

#include "Matrix.h"
#include "ConcreteMatrix.h"

class RectangularMatrix : public ConcreteMatrix {
public:
    RectangularMatrix(int rows, int columns);
    void display() override;

    std::unique_ptr<Matrix> add(const Matrix &other) const;

    std::unique_ptr<Matrix> subtract(const Matrix &other) const;

    std::unique_ptr<Matrix> multiply(const Matrix &other) const;

    size_t numRows() const;

    size_t numCols() const;

    std::unique_ptr<Matrix> multiplyRecursive(const Matrix &other) const;

    std::unique_ptr<Matrix> scalarMultiply(int scalar) const;

    std::unique_ptr<Matrix> transpose() const;
    int getElement(size_t row, size_t col) const override {
        return data[row][col];
    }

    void setElement(size_t row, size_t col, int value) override {
        data[row][col] = value;
    }
};

#endif // RECTANGULARMATRIX_H
