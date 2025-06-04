#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <iostream>

class Vector; // Forward declaration (sẽ dùng cho A3)

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructors và destructor
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other); // Copy constructor
    ~Matrix();

    // Operator overloads
    Matrix& operator=(const Matrix& other);
    Matrix operator+() const;
    Matrix operator-() const;
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(double scalar) const;

    // Accessors
    double& operator()(int i, int j);       // 1-based indexing
    double operator()(int i, int j) const;

    int NumRows() const;
    int NumCols() const;

    void Print() const;

    // Math methods
    double Determinant() const;
    Matrix Inverse() const;
    Matrix PseudoInverse() const;
};

#endif
