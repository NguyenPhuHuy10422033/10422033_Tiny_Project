#include "LinearSystem.h"
#include <cassert>
#include <cmath>
#include <stdexcept>

// Constructor
LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
    : mSize(A.NumRows()) {
    assert(A.NumRows() == A.NumCols());
    assert(A.NumRows() == b.Size());
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

// Destructor
LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

// Gaussian Elimination with partial pivoting
Vector LinearSystem::Solve() const {
    int n = mSize;
    Matrix A(*mpA);  // Make copies to work on
    Vector b(*mpb);
    Vector x(n);

    for (int i = 1; i <= n; ++i) {
        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k <= n; ++k) {
            if (std::fabs(A(k, i)) > std::fabs(A(maxRow, i))) {
                maxRow = k;
            }
        }
        for (int j = 1; j <= n; ++j)
            std::swap(A(i, j), A(maxRow, j));
        std::swap(b(i), b(maxRow));

        // Elimination
        for (int k = i + 1; k <= n; ++k) {
            double factor = A(k, i) / A(i, i);
            for (int j = i; j <= n; ++j)
                A(k, j) -= factor * A(i, j);
            b(k) -= factor * b(i);
        }
    }

    // Back substitution
    for (int i = n; i >= 1; --i) {
        x(i) = b(i);
        for (int j = i + 1; j <= n; ++j)
            x(i) -= A(i, j) * x(j);
        x(i) /= A(i, i);
    }

    return x;
}

// Conjugate Gradient Method (for symmetric positive-definite matrices)
PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    // Symmetry check
    for (int i = 1; i <= mSize; ++i)
        for (int j = 1; j <= mSize; ++j)
            assert(std::fabs((*mpA)(i, j) - (*mpA)(j, i)) < 1e-9);
}

Vector PosSymLinSystem::Solve() const {
    int n = mSize;
    const Matrix& A = *mpA;
    const Vector& b = *mpb;

    Vector x(n); // start with x = 0
    Vector r = b;
    Vector p = r;
    double rs_old = r * r;

    for (int i = 0; i < n; ++i) {
        Vector Ap(n);
        for (int j = 1; j <= n; ++j) {
            Ap(j) = 0;
            for (int k = 1; k <= n; ++k)
                Ap(j) += A(j, k) * p(k);
        }

        double alpha = rs_old / (p * Ap);
        for (int j = 1; j <= n; ++j)
            x(j) += alpha * p(j);
        for (int j = 1; j <= n; ++j)
            r(j) -= alpha * Ap(j);

        double rs_new = r * r;
        if (std::sqrt(rs_new) < 1e-8)
            break;

        for (int j = 1; j <= n; ++j)
            p(j) = r(j) + (rs_new / rs_old) * p(j);
        rs_old = rs_new;
    }

    return x;
}
