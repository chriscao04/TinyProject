#include "Matrix.hpp"

void Matrix::allocateAndZero(int rows, int cols) {
    mData = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        mData[i] = new double[cols];
        for (int j = 0; j < cols; ++j)
            mData[i][j] = 0.0;
    }
}

Matrix::Matrix(int numRows, int numCols)
    : mNumRows(numRows), mNumCols(numCols) {
    allocateAndZero(numRows, numCols);
}

Matrix::Matrix(const Matrix& other)
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    allocateAndZero(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i)
        delete[] mData[i];
    delete[] mData;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        allocateAndZero(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; ++i)
            for (int j = 0; j < mNumCols; ++j)
                mData[i][j] = other.mData[i][j];
    }
    return *this;
}

int Matrix::numRows() const { return mNumRows; }
int Matrix::numCols() const { return mNumCols; }

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}
const double& Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

Matrix Matrix::operator+() const { return *this; }
Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = -mData[i][j];
    return result;
}
Matrix Matrix::operator+(const Matrix& rhs) const {
    assert(mNumRows == rhs.mNumRows && mNumCols == rhs.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] + rhs.mData[i][j];
    return result;
}
Matrix Matrix::operator-(const Matrix& rhs) const {
    assert(mNumRows == rhs.mNumRows && mNumCols == rhs.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] - rhs.mData[i][j];
    return result;
}
Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] * scalar;
    return result;
}
Matrix Matrix::operator*(const Matrix& rhs) const {
    assert(mNumCols == rhs.mNumRows);
    Matrix result(mNumRows, rhs.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < rhs.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result.mData[i][j] += mData[i][k] * rhs.mData[k][j];
    return result;
}

// Determinant
double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    if (mNumRows == 1) return mData[0][0];
    if (mNumRows == 2)
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    double det = 0.0;
    for (int p = 0; p < mNumCols; ++p) {
        Matrix subMat(mNumRows - 1, mNumCols - 1);
        for (int i = 1; i < mNumRows; ++i) {
            int sub_j = 0;
            for (int j = 0; j < mNumCols; ++j) {
                if (j == p) continue;
                subMat.mData[i - 1][sub_j] = mData[i][j];
                ++sub_j;
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * mData[0][p] * subMat.determinant();
    }
    return det;
}

// Inverse (using Gauss-Jordan elimination)
Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix aug(n, 2 * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            aug.mData[i][j] = mData[i][j];
        for (int j = n; j < 2 * n; ++j)
            aug.mData[i][j] = (i == (j - n)) ? 1.0 : 0.0;
    }
    for (int i = 0; i < n; ++i) {
        double pivot = aug.mData[i][i];
        assert(pivot != 0);
        for (int j = 0; j < 2 * n; ++j)
            aug.mData[i][j] /= pivot;
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = aug.mData[k][i];
            for (int j = 0; j < 2 * n; ++j)
                aug.mData[k][j] -= factor * aug.mData[i][j];
        }
    }
    Matrix inv(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv.mData[i][j] = aug.mData[i][j + n];
    return inv;
}

// Pseudo-inverse (Moore-Penrose)
Matrix Matrix::pseudoInverse() const {
    if (mNumRows == mNumCols && determinant() != 0)
        return inverse();
    std::cerr << "Pseudo-inverse not implemented for non-square matrices.\n";
    return Matrix(1, 1);
}