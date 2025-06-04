#include <iostream>
#include "Vector.h"

int main() {
    Vector v1(3);
    v1(1) = 1.0;
    v1(2) = 2.0;
    v1(3) = 3.0;

    std::cout << "Vector v1: ";
    v1.Print();

    Vector v2 = v1 * 2.0;
    std::cout << "Vector v2 = v1 * 2: ";
    v2.Print();

    Vector v3 = v1 + v2;
    std::cout << "Vector v3 = v1 + v2: ";
    v3.Print();

    Vector v4 = v3 - v1;
    std::cout << "Vector v4 = v3 - v1: ";
    v4.Print();

    double dot = v1 * v2;
    std::cout << "Dot product v1 * v2 = " << dot << std::endl;

    return 0;
}
