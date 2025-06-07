#include "Vector.h"
#include <cassert>
#include <iostream>

using namespace std;

Vector::Vector(int size) : mSize(size), mData(new double[size]()) {}

Vector::Vector(const Vector& v) : mSize(v.mSize), mData(new double[v.mSize]) {
    for (int i = 0; i < mSize; ++i) mData[i] = v.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
        delete[] mData;
        mSize = v.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) mData[i] = v.mData[i];
    }
    return *this;
}

int Vector::size() const { return mSize; }

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

const double& Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

const double& Vector::operator()(int index) const {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = -mData[i];
    return result;
}

Vector Vector::operator+(const Vector& v) const {
    assert(mSize == v.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + v.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& v) const {
    assert(mSize == v.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - v.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

double Vector::operator*(const Vector& v) const {
    assert(mSize == v.mSize);
    double dot = 0.0;
    for (int i = 0; i < mSize; ++i)
        dot += mData[i] * v.mData[i];
    return dot;
}