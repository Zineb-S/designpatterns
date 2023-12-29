//
// Created by user on 12/29/2023.
//

#ifndef DEVOIR_LOGGINGOBSERVER_H
#define DEVOIR_LOGGINGOBSERVER_H


#include "Matrix.h"
#include "Observer.h"

class LoggingObserver : public Observer {
public:
    void update(const std::string& operation, const Matrix& matrix) override {
        std::cout << "Operation: " << operation << " on matrix: " << &matrix << std::endl;
        // Log the operation details...
    }
};



#endif //DEVOIR_LOGGINGOBSERVER_H
