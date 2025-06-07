#pragma once
#include <cassert>
#include <iostream>

class Vector {
private:
    int mSize;
    double* mData;
public:
    Vector(int size);
    Vector(const Vector& v);
    ~Vector();
    Vector& operator=(const Vector& v);

    int size() const;

    double& operator[](int index);
    const double& operator[](int index) const;

    double& operator()(int index);
    const double& operator()(int index) const;

    Vector operator+() const;
    Vector operator-() const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(double scalar) const;
    double operator*(const Vector& v) const;
};