#include "LinearSystem.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;

LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
    : mSize(A.numRows()), mpA(new Matrix(A)), mpb(new Vector(b)) {
    assert(A.numRows() == A.numCols());
    assert(A.numRows() == b.size());
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() {
    int n = mSize;
    Matrix A(*mpA);
    Vector b(*mpb);
    for (int k = 0; k < n; ++k) {
        int maxRow = k;
        for (int i = k + 1; i < n; ++i)
            if (abs(A(k+1, k+1)) > abs(A(maxRow+1, k+1)))
                maxRow = i;
        for (int j = 0; j < n; ++j) swap(A(k+1, j+1), A(maxRow+1, j+1));
        swap(b[k], b[maxRow]);
        for (int i = k + 1; i < n; ++i) {
            double factor = A(i+1, k+1) / A(k+1, k+1);
            for (int j = k; j < n; ++j)
                A(i+1, j+1) -= factor * A(k+1, j+1);
            b[i] -= factor * b[k];
        }
    }
    Vector x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= A(i+1, j+1) * x[j];
        x[i] /= A(i+1, i+1);
    }
    return x;
}

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    assert(mpA->numRows() == mpA->numCols());
    for (int i = 1; i <= mpA->numRows(); ++i)
        for (int j = 1; j <= mpA->numCols(); ++j)
            assert((*mpA)(i, j) == (*mpA)(j, i));
}

Vector PosSymLinSystem::Solve() {
    int n = mSize;
    Vector x(n);
    Vector r = *mpb;
    Vector p = r;
    double rsold = 0.0;
    for (int i = 0; i < n; ++i) rsold += r[i] * r[i];

    for (int iter = 0; iter < n * 10; ++iter) {
        Vector Ap(n);
        for (int i = 0; i < n; ++i) {
            Ap[i] = 0.0;
            for (int j = 0; j < n; ++j)
                Ap[i] += (*mpA)(i+1, j+1) * p[j];
        }
        double alpha = rsold;
        double denom = 0.0;
        for (int i = 0; i < n; ++i) denom += p[i] * Ap[i];
        alpha /= denom;
        for (int i = 0; i < n; ++i) x[i] += alpha * p[i];
        for (int i = 0; i < n; ++i) r[i] -= alpha * Ap[i];
        double rsnew = 0.0;
        for (int i = 0; i < n; ++i) rsnew += r[i] * r[i];
        if (sqrt(rsnew) < 1e-10) break;
        for (int i = 0; i < n; ++i) p[i] = r[i] + (rsnew / rsold) * p[i];
        rsold = rsnew;
    }
    return x;
}