#include "Vector.h"
#include <cassert>

Vector::Vector(int size) : mSize(size) {
    assert(size > 0);
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = 0.0;
}

Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;
    delete[] mData;
    mSize = other.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
    return *this;
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = -mData[i];
    return result;
}

Vector Vector::operator+(const Vector& v) const {
    assert(mSize == v.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + v.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& v) const {
    assert(mSize == v.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - v.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

double Vector::operator*(const Vector& v) const {
    assert(mSize == v.mSize);
    double result = 0.0;
    for (int i = 0; i < mSize; ++i)
        result += mData[i] * v.mData[i];
    return result;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

double Vector::operator()(int index) const {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

int Vector::Size() const {
    return mSize;
}

void Vector::Print() const {
    for (int i = 0; i < mSize; ++i)
        std::cout << mData[i] << " ";
    std::cout << std::endl;
}
