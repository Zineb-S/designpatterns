#ifndef OBSERVER_H
#define OBSERVER_H

#include "Matrix.h"
#include <string>

class Observer {
public:
    // Update method that will be called when the subject (Matrix) changes
    virtual void update(const std::string& operation, const Matrix& matrix) = 0;

    // Virtual destructor for proper cleanup of derived classes
    virtual ~Observer() {}
};

#endif // OBSERVER_H
