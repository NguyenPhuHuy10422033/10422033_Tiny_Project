#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructor và Destructor
    Vector(int size);
    Vector(const Vector& other); // Copy constructor
    ~Vector();

    // Operator Overloads
    Vector& operator=(const Vector& other);   // Assignment
    Vector operator+() const;                 // Unary +
    Vector operator-() const;                 // Unary -
    Vector operator+(const Vector& v) const;  // Vector + Vector
    Vector operator-(const Vector& v) const;  // Vector - Vector
    Vector operator*(double scalar) const;    // Vector * scalar
    double operator*(const Vector& v) const;  // Dot product

    double& operator[](int index);            // Access with bounds check [0-based]
    double operator[](int index) const;
    double& operator()(int index);            // Access with 1-based index
    double operator()(int index) const;

    int Size() const;                         // Get size
    void Print() const;                       // Print elements
};

#endif
