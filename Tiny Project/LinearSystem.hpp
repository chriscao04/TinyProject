#pragma once
#include "Matrix.hpp"
#include "Vector.h"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;
private:
    LinearSystem();
    LinearSystem(const LinearSystem&);
public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();
    virtual Vector Solve();
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    Vector Solve() override;
};