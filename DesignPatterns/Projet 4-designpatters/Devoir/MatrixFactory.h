#ifndef MATRIXFACTORY_H
#define MATRIXFACTORY_H

#include "ColumnMatrix.h"
#include "RectangularMatrix.h"
#include "Matrix.h"
#include "SquareMatrix.h"
#include "RowMatrix.h"

class MatrixFactory {
public:
    virtual Matrix* createMatrix(int dimension1, int dimension2 = 0) = 0;
    virtual ~MatrixFactory() {}
};

class SquareMatrixFactory : public MatrixFactory {
public:
    Matrix* createMatrix(int size, int unused = 0) override {
        return new SquareMatrix(size);
    }
};

class RowMatrixFactory : public MatrixFactory {
public:
    Matrix* createMatrix(int size, int unused = 0) override {
        return new RowMatrix(size);
    }
};

class ColumnMatrixFactory : public MatrixFactory {
public:
    Matrix* createMatrix(int size, int unused = 0) override {
        return new ColumnMatrix(size);
    }
};

class RectangularMatrixFactory : public MatrixFactory {
public:
    Matrix* createMatrix(int rows, int columns) override {
        return new RectangularMatrix(rows, columns);
    }
};

#endif // MATRIXFACTORY_H
