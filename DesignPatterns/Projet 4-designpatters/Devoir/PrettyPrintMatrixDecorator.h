#ifndef PRETTYPRINTMATRIXDECORATOR_H
#define PRETTYPRINTMATRIXDECORATOR_H

#include "MatrixDecorator.h"

class PrettyPrintMatrixDecorator : public MatrixDecorator {
public:
    PrettyPrintMatrixDecorator(Matrix* matrix) : MatrixDecorator(matrix) {}

    void display() override {
        std::cout << "----- Pretty Matrix -----\n";
        MatrixDecorator::display();
        std::cout << "----- End of Pretty Matrix -----\n";
    }
};

#endif // PRETTYPRINTMATRIXDECORATOR_H
