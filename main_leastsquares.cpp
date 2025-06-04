#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LeastSquaresSolver.h"

int main() {
    // A là ma trận 4x2 (over-determined)
    Matrix A(4, 2);
    A(1, 1) = 1; A(1, 2) = 1;
    A(2, 1) = 2; A(2, 2) = 1;
    A(3, 1) = 3; A(3, 2) = 1;
    A(4, 1) = 4; A(4, 2) = 1;

    Vector b(4);
    b(1) = 6;
    b(2) = 5;
    b(3) = 7;
    b(4) = 10;

    LeastSquaresSolver solver(A, b);
    Vector x = solver.Solve();

    std::cout << "Least squares solution (Ax ≈ b):" << std::endl;
    x.Print(); // Output gần đúng nghiệm x sao cho Ax ≈ b

    return 0;
}
