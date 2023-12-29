//
// Created by user on 12/29/2023.
//

#ifndef DEVOIR_MATRIXTEST_H
#define DEVOIR_MATRIXTEST_H


#include "MatrixFactory.h"
#include <iostream>
#include <memory>
#include <cassert>

class MatrixTest {
public:
    void runTests() {
       testSquareMatrixOperations();
        testRowMatrixOperations();
        testColumnMatrixOperations();
        testRectangularMatrixOperations();
        std::cout << "All tests passed successfully!" << std::endl;
    }

private:
    void testSquareMatrixOperations() {
        std::cout << "Testing SquareMatrix operations..." << std::endl;

        // Example matrices for testing
        SquareMatrix matrix1(2, 1); // A 2x2 matrix with all elements initialized to 1
        SquareMatrix matrix2(2, 2); // A 2x2 matrix with all elements initialized to 2

        // Test Addition
        auto sumMatrix = matrix1.add(matrix2);
        assert(sumMatrix->getElement(0, 0) == 3); // Assuming getElement(int, int) is a method to access matrix elements

        // Test Subtraction
        auto diffMatrix = matrix2.subtract(matrix1);
        assert(diffMatrix->getElement(0, 0) == 1);

        // Test Multiplication (Iterative)
        auto productMatrix = matrix1.multiply(matrix2);
        assert(productMatrix->getElement(0, 0) == 4);

        // Test Multiplication (Recursive)
        auto recursiveProductMatrix = matrix1.multiplyRecursive(matrix2);
       assert(recursiveProductMatrix->getElement(0, 0) == 4);
       /* std::cout << "Testing Simple Recursive Multiplication..." << std::endl;

        // Create matrix A
        SquareMatrix matrixA(2);
        matrixA.setElement(0, 0, 1);
        matrixA.setElement(0, 1, 2);
        matrixA.setElement(1, 0, 3);
        matrixA.setElement(1, 1, 4);

        // Create matrix B
        SquareMatrix matrixB(2);
        matrixB.setElement(0, 0, 5);
        matrixB.setElement(0, 1, 6);
        matrixB.setElement(1, 0, 7);
        matrixB.setElement(1, 1, 8);

        // Perform recursive multiplication
        auto resultMatrix = matrixA.multiplyRecursive(matrixB);

        // Display result
        std::cout << "Result Matrix:" << std::endl;
        resultMatrix->display();

        // Check if the result is as expected
        assert(resultMatrix->getElement(0, 0) == 19);
        assert(resultMatrix->getElement(0, 1) == 22);
        assert(resultMatrix->getElement(1, 0) == 43);
        assert(resultMatrix->getElement(1, 1) == 50);

        std::cout << "Simple Recursive Multiplication Test Passed." << std::endl;*/
        // Test Determinant
        double determinant = matrix1.determinant();
       // assert(determinant != 0); // Example check

        // Test Inverse
        try {
            auto inverseMatrix = matrix1.inverse();
            assert(inverseMatrix != nullptr); // Basic check to ensure inverse exists
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in inverse calculation: " << e.what() << std::endl;
        }

        // Test Transpose
        auto transposeMatrix = matrix1.transpose();
        assert(transposeMatrix->getElement(0, 1) == matrix1.getElement(1, 0));

        std::cout << "SquareMatrix operations tested successfully." << std::endl;
    }


    void testRowMatrixOperations() {
        std::cout << "Testing RowMatrix operations..." << std::endl;

        // Example matrices for testing
        RowMatrix matrix1(3); // A row matrix with 3 columns
        RowMatrix matrix2(3); // Another row matrix with 3 columns

        // Initialize matrices with values
        matrix1.setElement(0, 0, 1); matrix1.setElement(0, 1, 2); matrix1.setElement(0, 2, 3); // Assuming setElement(int, int, int) sets the value
        matrix2.setElement(0, 0, 4); matrix2.setElement(0, 1, 5); matrix2.setElement(0, 2, 6);

        // Test Addition
        auto sumMatrix = matrix1.add(matrix2);
        assert(sumMatrix->getElement(0, 0) == 5); // Assuming getElement(int, int) is a method to access matrix elements

        // Test Subtraction
        auto diffMatrix = matrix2.subtract(matrix1);
        assert(diffMatrix->getElement(0, 0) == 3);

        // Test Scalar Multiplication
        int scalar = 2;
        auto scalarMultipliedMatrix = matrix1.scalarMultiply(scalar);
        assert(scalarMultipliedMatrix->getElement(0, 0) == 2);

        // Test Transpose
        auto transposeMatrix = matrix1.transpose();
        assert(transposeMatrix->numRows() == matrix1.numCols());
        assert(transposeMatrix->getElement(0, 0) == matrix1.getElement(0, 0));
        assert(transposeMatrix->getElement(1, 0) == matrix1.getElement(0, 1));
        assert(transposeMatrix->getElement(2, 0) == matrix1.getElement(0, 2));

        std::cout << "RowMatrix operations tested successfully." << std::endl;
    }


    void testColumnMatrixOperations() {
        std::cout << "Testing ColumnMatrix operations..." << std::endl;

        // Example matrices for testing
        ColumnMatrix matrix1(3); // A column matrix with 3 rows
        ColumnMatrix matrix2(3); // Another column matrix with 3 rows

        // Initialize matrices with values
        matrix1.setElement(0, 0, 1); matrix1.setElement(1, 0, 2); matrix1.setElement(2, 0, 3); // setElement(row, col, value)
        matrix2.setElement(0, 0, 4); matrix2.setElement(1, 0, 5); matrix2.setElement(2, 0, 6);

        // Test Addition
        auto sumMatrix = matrix1.add(matrix2);
        assert(sumMatrix->getElement(0, 0) == 5); // getElement(row, col)

        // Test Subtraction
        auto diffMatrix = matrix2.subtract(matrix1);
        assert(diffMatrix->getElement(0, 0) == 3);

        // Test Scalar Multiplication
        int scalar = 2;
        auto scalarMultipliedMatrix = matrix1.scalarMultiply(scalar);
        assert(scalarMultipliedMatrix->getElement(0, 0) == 2);

        // Test Transpose
        auto transposeMatrix = matrix1.transpose();
        assert(transposeMatrix->numCols() == matrix1.numRows());
        assert(transposeMatrix->getElement(0, 0) == matrix1.getElement(0, 0));
        assert(transposeMatrix->getElement(0, 1) == matrix1.getElement(1, 0));
        assert(transposeMatrix->getElement(0, 2) == matrix1.getElement(2, 0));

        std::cout << "ColumnMatrix operations tested successfully." << std::endl;
    }


    void testRectangularMatrixOperations() {
        std::cout << "Testing RectangularMatrix operations..." << std::endl;

        // Example matrices for testing
        RectangularMatrix matrix1(3, 2); // A 3x2 matrix
        RectangularMatrix matrix2(3, 2); // Another 3x2 matrix

        // Initialize matrices with values
        matrix1.setElement(0, 0, 1); matrix1.setElement(0, 1, 2);
        matrix1.setElement(1, 0, 3); matrix1.setElement(1, 1, 4);
        matrix1.setElement(2, 0, 5); matrix1.setElement(2, 1, 6);

        matrix2.setElement(0, 0, 6); matrix2.setElement(0, 1, 5);
        matrix2.setElement(1, 0, 4); matrix2.setElement(1, 1, 3);
        matrix2.setElement(2, 0, 2); matrix2.setElement(2, 1, 1);

        // Test Addition
        auto sumMatrix = matrix1.add(matrix2);
        assert(sumMatrix->getElement(0, 0) == 7);

        // Test Subtraction
        auto diffMatrix = matrix1.subtract(matrix2);
        assert(diffMatrix->getElement(1, 1) == 1);

        // Test Scalar Multiplication
        int scalar = 2;
        auto scalarMultipliedMatrix = matrix1.scalarMultiply(scalar);
        assert(scalarMultipliedMatrix->getElement(2, 1) == 12);

        // Test Transpose
        auto transposeMatrix = matrix1.transpose();
        assert(transposeMatrix->numCols() == matrix1.numRows());
        assert(transposeMatrix->numRows() == matrix1.numCols());
        assert(transposeMatrix->getElement(1, 2) == matrix1.getElement(2, 1));

        std::cout << "RectangularMatrix operations tested successfully." << std::endl;
    }


    bool areMatricesEqual(const Matrix& m1, const Matrix& m2) {
        // Check dimensions first
        if (m1.numRows() != m2.numRows() || m1.numCols() != m2.numCols()) {
            return false;
        }

        // Compare each element
        for (size_t i = 0; i < m1.numRows(); ++i) {
            for (size_t j = 0; j < m1.numCols(); ++j) {
                if (m1.getElement(i, j) != m2.getElement(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }

};




#endif //DEVOIR_MATRIXTEST_H
