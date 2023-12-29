#ifndef ROWMATRIX_H
#define ROWMATRIX_H

#include "Matrix.h"
#include "ConcreteMatrix.h"
#include <vector>

class RowMatrix : public ConcreteMatrix {
public:
    explicit RowMatrix(int columns);
    void display() override;

    size_t numRows() const override;
    size_t numCols() const override;

    std::unique_ptr<Matrix> add(const Matrix& other) const override;
    std::unique_ptr<Matrix> subtract(const Matrix& other) const override;
    std::unique_ptr<Matrix> multiply(const Matrix& other) const override;
    std::unique_ptr<Matrix> multiplyRecursive(const Matrix &other) const override;
    std::unique_ptr<Matrix> scalarMultiply(int scalar) const override;
    std::unique_ptr<Matrix> transpose() const override;



    std::vector<std::vector<int>> data;

    int getElement(size_t row, size_t col) const override {
        return data[0][col];
    }

    void setElement(size_t row, size_t col, int value) override {
        data[0][col] = value;
    }
};

#endif // ROWMATRIX_H
