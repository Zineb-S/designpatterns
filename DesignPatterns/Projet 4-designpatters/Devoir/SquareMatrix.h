#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"
#include "ConcreteMatrix.h"
#include <vector>
#include <memory>

class SquareMatrix : public ConcreteMatrix  {
public:
    explicit SquareMatrix(int size);
    SquareMatrix(int size, double initialValue);
    void display() override;

    std::unique_ptr<Matrix> add(const Matrix &other) const override;
    std::unique_ptr<Matrix> subtract(const Matrix &other) const override;
    std::unique_ptr<Matrix> multiply(const Matrix &other) const override;
    std::unique_ptr<Matrix> multiplyRecursive(const Matrix &other) const override;

    size_t numRows() const override;
    size_t numCols() const override;

    static std::unique_ptr<SquareMatrix> multiplyRecursiveHelper(const SquareMatrix& a, const SquareMatrix& b);
    std::unique_ptr<Matrix> scalarMultiply(int scalar) const override;
    double determinant() const;
    std::unique_ptr<Matrix> inverse() const;

    std::unique_ptr<Matrix> transpose() const;

    int getElement(size_t row, size_t col) const override;

    void setElement(size_t row, size_t col, int value) override;

private:
    SquareMatrix createSubMatrix(int excludingRow, int excludingColumn) const;
    std::vector<std::vector<double>> data;

};

#endif // SQUAREMATRIX_H
