#include <iostream>
#include "Matrix.h"

int main() {
    Matrix A(2, 2);
    A(1, 1) = 1; A(1, 2) = 2;
    A(2, 1) = 3; A(2, 2) = 4;

    Matrix B(2, 2);
    B(1, 1) = 5; B(1, 2) = 6;
    B(2, 1) = 7; B(2, 2) = 8;

    std::cout << "Matrix A:\n";
    A.Print();

    std::cout << "\nMatrix B:\n";
    B.Print();

    Matrix C = A + B;
    std::cout << "\nA + B:\n";
    C.Print();

    Matrix D = A * B;
    std::cout << "\nA * B:\n";
    D.Print();

    return 0;
}
