//
// Created by user on 12/29/2023.
//

#ifndef DEVOIR_MATRIXSUBJECT_H
#define DEVOIR_MATRIXSUBJECT_H


#include "Observer.h"

class MatrixSubject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify(const std::string& operation, const Matrix& matrix) = 0;
    virtual ~MatrixSubject() {}
};



#endif //DEVOIR_MATRIXSUBJECT_H
