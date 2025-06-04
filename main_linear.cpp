#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

int main() {
    Matrix A(3, 3);
    A(1, 1) = 4; A(1, 2) = 1; A(1, 3) = 2;
    A(2, 1) = 1; A(2, 2) = 3; A(2, 3) = 0;
    A(3, 1) = 2; A(3, 2) = 0; A(3, 3) = 5;

    Vector b(3);
    b(1) = 4;
    b(2) = 5;
    b(3) = 6;

    std::cout << "Solving Ax = b using Gaussian elimination:\n";
    LinearSystem ls(A, b);
    Vector x = ls.Solve();
    x.Print();

    std::cout << "\nSolving Ax = b using Conjugate Gradient (symmetric A):\n";
    PosSymLinSystem psls(A, b);
    Vector x2 = psls.Solve();
    x2.Print();

    return 0;
}
