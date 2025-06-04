#include "LinearRegression.h"
#include "LeastSquaresSolver.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>

LinearRegression::LinearRegression()
    : A(1, 1), b(1), coeff(1), m(0), n(6) {}

void LinearRegression::LoadDataFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    std::vector<std::vector<double>> feature_rows;
    std::vector<double> prp_values;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(ss, token, ','))
            tokens.push_back(token);

        if (tokens.size() < 10) continue;

        // Parse the 6 relevant features: MYCT, MMIN, MMAX, CACH, CHMIN, CHMAX (index 2-7)
        std::vector<double> row;
        for (int i = 2; i <= 7; ++i)
            row.push_back(std::stod(tokens[i]));

        // Parse PRP (index 8)
        prp_values.push_back(std::stod(tokens[8]));
        feature_rows.push_back(row);
    }

    m = feature_rows.size();
    A = Matrix(m, n);
    b = Vector(m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            A(i + 1, j + 1) = feature_rows[i][j];
        b(i + 1) = prp_values[i];
    }
}

void LinearRegression::Train() {
    LeastSquaresSolver solver(A, b);
    coeff = solver.Solve();
}

double LinearRegression::Evaluate(const std::string& testFile) {
    std::ifstream file(testFile);
    std::string line;

    double totalSquaredError = 0.0;
    int count = 0;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(ss, token, ','))
            tokens.push_back(token);

        if (tokens.size() < 10) continue;

        std::vector<double> x;
        for (int i = 2; i <= 7; ++i)
            x.push_back(std::stod(tokens[i]));

        double y_true = std::stod(tokens[8]);
        double y_pred = 0.0;

        for (int i = 0; i < 6; ++i)
            y_pred += coeff(i + 1) * x[i];

        double error = y_true - y_pred;
        totalSquaredError += error * error;
        count++;
    }

    return std::sqrt(totalSquaredError / count); // RMSE
}

void LinearRegression::PrintCoefficients() const {
    std::cout << "Model coefficients:\n";
    for (int i = 1; i <= coeff.Size(); ++i)
        std::cout << "x" << i << " = " << coeff(i) << std::endl;
}
