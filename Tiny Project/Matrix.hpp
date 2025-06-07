#pragma once
#include <cassert>
#include <iostream>
#include "Vector.h"

class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;
    void allocateAndZero(int rows, int cols);
public:
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();
    Matrix& operator=(const Matrix& other);

    int numRows() const;
    int numCols() const;

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    Matrix operator+() const;
    Matrix operator-() const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix& rhs) const;

    double determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse() const;
};