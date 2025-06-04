#include "LeastSquaresSolver.h"
#include <cassert>
#include <cmath>

// Constructor
LeastSquaresSolver::LeastSquaresSolver(const Matrix& inputA, const Vector& inputb)
    : A(inputA), b(inputb) {
    mRows = A.NumRows();
    mCols = A.NumCols();
    assert(b.Size() == mRows);
}

Vector LeastSquaresSolver::Solve() const {
    // A^T
    Matrix At(mCols, mRows);
    for (int i = 1; i <= mCols; ++i)
        for (int j = 1; j <= mRows; ++j)
            At(i, j) = A(j, i);

    // A^T * A
    Matrix AtA = At * A;

    // A^T * b
    Vector Atb(mCols);
    for (int i = 1; i <= mCols; ++i) {
        Atb(i) = 0;
        for (int j = 1; j <= mRows; ++j)
            Atb(i) += At(i, j) * b(j);
    }

    // Giải (A^T A) x = A^T b
    LinearSystem ls(AtA, Atb);
    return ls.Solve();
}
