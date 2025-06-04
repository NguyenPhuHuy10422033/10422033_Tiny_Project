#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    // Constructor
    LinearSystem(const Matrix& A, const Vector& b);

    // Virtual destructor
    virtual ~LinearSystem();

    // Virtual solve method (Gaussian elimination)
    virtual Vector Solve() const;
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    Vector Solve() const override; // Override using Conjugate Gradient
};

#endif
