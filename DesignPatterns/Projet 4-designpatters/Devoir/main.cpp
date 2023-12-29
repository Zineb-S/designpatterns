#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MatrixFactory.h"
#include "MatrixTest.h"
#include "PrettyPrintMatrixDecorator.h"
#include "LogMatrixOperationsDecorator.h"
#include "LoggingObserver.h"

Matrix* decorateMatrix(Matrix* matrix) {
    Matrix* prettyMatrix = new PrettyPrintMatrixDecorator(matrix);
    return new LogMatrixOperationsDecorator(prettyMatrix);
}

int main() {
    MatrixTest test;
    test.runTests();
    std::cout << "Hello, World!" << std::endl;
    srand(static_cast<unsigned>(time(NULL)));
    LoggingObserver logger;
    while (true) {
        std::cout << "Choose the type of matrix you want:" << std::endl;
        std::cout << "1. Square Matrix" << std::endl;
        std::cout << "2. Row Matrix" << std::endl;
        std::cout << "3. Column Matrix" << std::endl;
        std::cout << "4. Rectangular Matrix" << std::endl;
        std::cout << "Enter your choice (1-4): ";

        int choice;
        std::cin >> choice;

        MatrixFactory* factory = nullptr;
        Matrix* matrix = nullptr;
        Matrix* decoratedMatrix = nullptr;

        int rows, columns;

        switch (choice) {
            case 1:
                std::cout << "Enter size for Square Matrix: ";
                std::cin >> rows;
                factory = new SquareMatrixFactory();
                matrix = factory->createMatrix(rows);

                break;
            case 2:
                std::cout << "Enter number of columns for Row Matrix: ";
                std::cin >> columns;
                factory = new RowMatrixFactory();
                matrix = factory->createMatrix(columns);
                break;
            case 3:
                std::cout << "Enter number of rows for Column Matrix: ";
                std::cin >> rows;
                factory = new ColumnMatrixFactory();
                matrix = factory->createMatrix(rows);
                break;
            case 4:
                do {
                    std::cout << "Enter number of rows for Rectangular Matrix: ";
                    std::cin >> rows;
                    std::cout << "Enter number of columns: ";
                    std::cin >> columns;

                    if (rows == columns) {
                        std::cout << "For a rectangular matrix, rows and columns must be different. Please try again."
                                  << std::endl;
                    }
                } while (rows == columns);

                factory = new RectangularMatrixFactory();
                matrix = factory->createMatrix(rows, columns);
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                return 1;
        }
        bool isSquareMatrix = (choice == 1);
        decoratedMatrix = decorateMatrix(matrix);  // Decorate the matrix

        if (decoratedMatrix) {
            std::cout << "Generated Matrix:" << std::endl;
            decoratedMatrix->display();
        }
        if (auto concreteMatrix = dynamic_cast<ConcreteMatrix*>(matrix)) {
            concreteMatrix->attach(&logger);
        }
        if (matrix) {
            std::cout << "Generated Matrix:" << std::endl;
            matrix->display();

        }
        std::cout << "\nChoose the operation you want to perform:" << std::endl;
        std::cout << "1. Add" << std::endl;
        std::cout << "2. Subtract" << std::endl;
        std::cout << "3. Multiply (Iterative)" << std::endl;
        std::cout << "4. Multiply (Recursive) (Square matrices only)" << std::endl;
        std::cout << "5. Scalar Multiply" << std::endl;
        std::cout << "6. Determinant (Square matrices only)" << std::endl;
        std::cout << "7. Inverse (Square matrices only)" << std::endl;
        std::cout << "8. Transpose" << std::endl;
        std::cout << "Enter your choice: ";

        int operationChoice;
        std::cin >> operationChoice;
        // Check for square matrix specific operations
        if ((operationChoice == 6 || operationChoice == 7) && !isSquareMatrix) {
            std::cout << "This operation can only be performed on square matrices." << std::endl;
            // Optionally loop back to operation choice or exit
            return 1;
        }
        Matrix *matrix2 = nullptr;
        int secondMatrixRows, secondMatrixColumns;

        // Creating a second matrix for operations that require it
        if (operationChoice == 1 || operationChoice == 2 || operationChoice == 3 || operationChoice == 4) {
            switch (choice) {
                case 1: // Square Matrix
                    matrix2 = (new SquareMatrixFactory())->createMatrix(rows);
                    break;
                case 2: // Row Matrix
                    if (operationChoice == 3) { // If operation is multiplication
                        secondMatrixColumns = columns; // Number of rows for the second matrix matches the number of columns in the first
                        std::cout << "Enter number of columns for the second matrix: ";
                        std::cin >> secondMatrixColumns;
                        matrix2 = (new RectangularMatrixFactory())->createMatrix(columns,
                                                                                 secondMatrixColumns); // columns from the first matrix become rows for the second matrix
                    }
                    break;
                case 3: // Column Matrix
                    if (operationChoice == 3) {
                        std::cout << "Enter the length of the row for the second matrix (RowMatrix): ";
                        std::cin >> secondMatrixColumns; // Length of the row for RowMatrix
                        matrix2 = (new RowMatrixFactory())->createMatrix(secondMatrixColumns);
                    } else {
                        matrix2 = (new ColumnMatrixFactory())->createMatrix(rows);
                    }
                    break;
                case 4: // Rectangular Matrix
                    if (operationChoice == 3) {
                        std::cout << "Enter number of columns for the second matrix (for multiplication): ";
                        std::cin >> secondMatrixColumns;
                        matrix2 = (new RectangularMatrixFactory())->createMatrix(columns, secondMatrixColumns);
                    } else {
                        matrix2 = (new RectangularMatrixFactory())->createMatrix(rows, columns);
                    }
                    break;

            }
            std::cout << "Generated Second Matrix for Operation:" << std::endl;
            matrix2->display();
        }

        // Print the chosen operation
        switch (operationChoice) {
            case 1: {
                std::cout << "Performing Addition" << std::endl;
                try {
                    auto sumMatrix = matrix->add(*matrix2);
                    std::cout << "Result of Addition:" << std::endl;
                    sumMatrix->display();

                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }

                break;
            case 2:
                std::cout << "Performing Subtraction" << std::endl;
                try {
                    auto differenceMatrix = matrix->subtract(*matrix2);
                    std::cout << "Result of Subtraction:" << std::endl;
                    differenceMatrix->display();
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            case 3:
                std::cout << "Performing Iterative Multiplication" << std::endl;
                try {
                    auto productMatrix = matrix->multiply(*matrix2);
                    std::cout << "Result of Multiplication:" << std::endl;
                    productMatrix->display();
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            case 4:
                std::cout << "Performing Recursive Multiplication" << std::endl;
                try {
                    auto productMatrix = matrix->multiplyRecursive(*matrix2);
                    std::cout << "Result of Recursive Multiplication:" << std::endl;
                    productMatrix->display();
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            case 5:
                std::cout << "Performing Scalar Multiplication" << std::endl;
                int scalar;
                std::cout << "Enter scalar value: ";
                std::cin >> scalar;
                try {
                    auto scalarMultipliedMatrix = matrix->scalarMultiply(scalar);
                    std::cout << "Result of Scalar Multiplication:" << std::endl;
                    scalarMultipliedMatrix->display();
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            case 6:
                std::cout << "Calculating Determinant" << std::endl;
                if (isSquareMatrix) {
                    try {
                        SquareMatrix *squareMatrix = dynamic_cast<SquareMatrix *>(matrix);
                        if (squareMatrix) {
                            double det = squareMatrix->determinant();
                            std::cout << "Determinant: " << det << std::endl;
                        } else {
                            std::cout << "Error: Matrix is not square." << std::endl;
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "Error calculating determinant: " << e.what() << std::endl;
                    }
                } else {
                    std::cout << "Determinant can only be calculated for square matrices." << std::endl;
                }

                break;
            case 7: { // Inverse operation
                std::cout << "Calculating Inverse" << std::endl;
                try {
                    auto inverseMatrix = dynamic_cast<SquareMatrix *>(matrix)->inverse();
                    std::cout << "Inverse of the Matrix:" << std::endl;
                    inverseMatrix->display();
                } catch (const std::runtime_error &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }

            case 8: { // Transpose operation
                std::cout << "Performing Transpose" << std::endl;
                auto transposedMatrix = matrix->transpose();
                std::cout << "Transposed Matrix:" << std::endl;
                transposedMatrix->display();
                break;
            }
            default:
                std::cout << "Invalid operation choice!" << std::endl;
                break;
        }

        if (auto concreteMatrix = dynamic_cast<ConcreteMatrix*>(matrix)) {
            std::string operationDescription = "Performed operation: " + std::to_string(operationChoice);
            concreteMatrix->notify(operationDescription, *matrix);
        }

        std::cout << "\nWould you like to perform another operation? (y/n): ";
        char continueChoice;
        std::cin >> continueChoice;
        if (continueChoice == 'n' || continueChoice == 'N') {
            delete decoratedMatrix;
            delete matrix;
            delete factory;
            delete matrix2;
            break;
        }

    }

    return 0;
}
