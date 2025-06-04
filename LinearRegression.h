#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "Matrix.h"
#include "Vector.h"
#include <string>
#include <vector>

class LinearRegression {
private:
    Matrix A;     // Design matrix (m x n)
    Vector b;     // Target vector (PRP)
    Vector coeff; // Learned weights
    int m;        // Rows
    int n;        // Features

public:
    LinearRegression();
    void LoadDataFromCSV(const std::string& filename);
    void Train();
    double Evaluate(const std::string& testFile); // RMSE
    void PrintCoefficients() const;
};

#endif
