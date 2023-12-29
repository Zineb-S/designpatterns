//
// Created by user on 12/29/2023.
//

#ifndef DEVOIR_CONCRETEMATRIX_H
#define DEVOIR_CONCRETEMATRIX_H


#include "Observer.h"
#include "MatrixSubject.h"
#include <list>
class ConcreteMatrix : public Matrix, public MatrixSubject {
private:
    std::list<Observer*> observers;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.remove(observer);
    }

    void notify(const std::string& operation, const Matrix& matrix) override {
        for (Observer* observer : observers) {
            observer->update(operation, matrix);
        }
    }
    void notifyObservers(const std::string& operation) {
        for (Observer* observer : observers) {
            observer->update(operation, *this);
        }
    }
    // Matrix operations (like add, subtract, multiply...)
    // Inside each operation, call notify(...)
};


#endif //DEVOIR_CONCRETEMATRIX_H
