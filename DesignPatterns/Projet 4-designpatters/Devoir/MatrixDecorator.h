
#ifndef MATRIXDECORATOR_H
#define MATRIXDECORATOR_H
#include "Matrix.h"

class MatrixDecorator : public Matrix {
protected:
    Matrix* matrix; // Wrapped matrix object

public:
    MatrixDecorator(Matrix* matrix) : matrix(matrix) {}

    void display() override {
        matrix->display();
    }

    // Delegate all other Matrix methods to the wrapped matrix object
    std::unique_ptr<Matrix> add(const Matrix& other) const override {
        throw std::runtime_error("This is just a decorator");
    }

    std::unique_ptr<Matrix> subtract(const Matrix& other) const override {
        throw std::runtime_error("This is just a decorator");
    }

    std::unique_ptr<Matrix> multiply(const Matrix& other) const override {
        throw std::runtime_error("This is just a decorator");
    }
    std::unique_ptr<Matrix> multiplyRecursive(const Matrix &other) const override {
        throw std::runtime_error("This is just a decorator");
    }
    std::unique_ptr<Matrix> scalarMultiply(int scalar) const override {
        throw std::runtime_error("This is just a decorator");
    }
    std::unique_ptr<Matrix> transpose() const override {
        throw std::runtime_error("This is just a decorator");
    }
    virtual size_t numRows() const override {
        throw std::runtime_error("This is just a decorator");
    }
    virtual size_t numCols() const override {
        throw std::runtime_error("This is just a decorator");
    }
    virtual int getElement(size_t row, size_t col) const override {
        throw std::runtime_error("This is just a decorator");
    }
    virtual void setElement(size_t row, size_t col, int value) override {
        throw std::runtime_error("This is just a decorator");
    }
    virtual ~MatrixDecorator() {
        delete matrix;
    }
};


#endif // MATRIXDECORATOR_H
