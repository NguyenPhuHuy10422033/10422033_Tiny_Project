#include "Matrix.h"
#include <cmath>
#include <stdexcept>

// Constructor
Matrix::Matrix(int numRows, int numCols)
    : mNumRows(numRows), mNumCols(numCols) {
    assert(numRows > 0 && numCols > 0);
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = 0.0;
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i)
        delete[] mData[i];
    delete[] mData;
}

// Assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    // Cleanup
    for (int i = 0; i < mNumRows; ++i)
        delete[] mData[i];
    delete[] mData;

    // Copy
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    }
    return *this;
}

// Access with 1-based indexing
double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

double Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

int Matrix::NumRows() const {
    return mNumRows;
}

int Matrix::NumCols() const {
    return mNumCols;
}

Matrix Matrix::operator+() const {
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = -mData[i][j];
    return result;
}

Matrix Matrix::operator+(const Matrix& m) const {
    assert(mNumRows == m.mNumRows && mNumCols == m.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] + m.mData[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& m) const {
    assert(mNumRows == m.mNumRows && mNumCols == m.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] - m.mData[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& m) const {
    assert(mNumCols == m.mNumRows);
    Matrix result(mNumRows, m.mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < m.mNumCols; ++j) {
            result.mData[i][j] = 0.0;
            for (int k = 0; k < mNumCols; ++k)
                result.mData[i][j] += mData[i][k] * m.mData[k][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] * scalar;
    return result;
}

void Matrix::Print() const {
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j)
            std::cout << mData[i][j] << " ";
        std::cout << std::endl;
    }
}

// Determinant, Inverse, PseudoInverse sẽ được bổ sung phần sau (A3)

double Matrix::Determinant() const {
    throw std::runtime_error("Determinant() not yet implemented.");
}

Matrix Matrix::Inverse() const {
    throw std::runtime_error("Inverse() not yet implemented.");
}

Matrix Matrix::PseudoInverse() const {
    throw std::runtime_error("PseudoInverse() not yet implemented.");
}
