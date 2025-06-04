#ifndef LEASTSQUARESSOLVER_H
#define LEASTSQUARESSOLVER_H

#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

class LeastSquaresSolver {
private:
    Matrix A;
    Vector b;
    int mRows, mCols;

public:
    LeastSquaresSolver(const Matrix& inputA, const Vector& inputb);
    Vector Solve() const; // Pseudo-inverse: (A^T A)^-1 A^T b
};

#endif
