cmake_minimum_required(VERSION 3.27)
project(Devoir)

set(CMAKE_CXX_STANDARD 17)

add_executable(Devoir main.cpp
        Matrix.cpp
        Matrix.h
        MatrixFactory.cpp
        MatrixFactory.h
        RandomNumberGenerator.cpp
        RandomNumberGenerator.h
        ColumnMatrix.cpp
        ColumnMatrix.h
        RectangularMatrix.cpp
        RectangularMatrix.h
        SquareMatrix.cpp
        SquareMatrix.h
        RowMatrix.cpp
        RowMatrix.h
        MatrixTest.cpp
        MatrixTest.h
        MatrixDecorator.cpp
        MatrixDecorator.h
        PrettyPrintMatrixDecorator.cpp
        PrettyPrintMatrixDecorator.h
        LogMatrixOperationsDecorator.cpp
        LogMatrixOperationsDecorator.h
        Observer.cpp
        Observer.h
        MatrixSubject.cpp
        MatrixSubject.h
        ConcreteMatrix.cpp
        ConcreteMatrix.h
        LoggingObserver.cpp
        LoggingObserver.h
)
