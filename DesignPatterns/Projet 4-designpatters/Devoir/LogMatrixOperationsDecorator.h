#ifndef LOGMATRIXOPERATIONSDECORATOR_H
#define LOGMATRIXOPERATIONSDECORATOR_H

#include "MatrixDecorator.h"
#include <iostream>

class LogMatrixOperationsDecorator : public MatrixDecorator {
public:
    LogMatrixOperationsDecorator(Matrix* matrix) : MatrixDecorator(matrix) {}

    void display() override {
        std::cout << "Logging before displaying matrix.\n";
        MatrixDecorator::display();
        std::cout << "Logging after displaying matrix.\n";
    }
    // Implement other matrix operations with logging if needed...
};

#endif // LOGMATRIXOPERATIONSDECORATOR_H
