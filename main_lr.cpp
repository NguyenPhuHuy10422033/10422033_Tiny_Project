#include "LinearRegression.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

//  Hàm shuffle và chia dữ liệu
void ShuffleAndSplit(const std::string& inputFile,
                     const std::string& trainFile,
                     const std::string& testFile,
                     double trainRatio = 0.8) {
    std::ifstream inFile(inputFile);
    std::ofstream outTrain(trainFile);
    std::ofstream outTest(testFile);

    if (!inFile || !outTrain || !outTest) {
        std::cerr << "❌ Lỗi khi mở file!" << std::endl;
        return;
    }

    std::vector<std::string> allLines;
    std::string line;

    while (std::getline(inFile, line)) {
        if (!line.empty())
            allLines.push_back(line);
    }

    //  Shuffle
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allLines.begin(), allLines.end(), g);

    int total = allLines.size();
    int trainSize = static_cast<int>(trainRatio * total);

    for (int i = 0; i < total; ++i) {
        if (i < trainSize)
            outTrain << allLines[i] << "\n";
        else
            outTest << allLines[i] << "\n";
    }

    std::cout << "Shuffled and split " << total << " rows:\n"
              << "  - " << trainSize << " rows into train.data\n"
              << "  - " << (total - trainSize) << " rows into test.data\n";
}

int main() {
    //  Tự động chia dữ liệu
    ShuffleAndSplit("machine.data", "train.data", "test.data");

    //  Linear Regression
    LinearRegression model;
    model.LoadDataFromCSV("train.data");
    model.Train();
    model.PrintCoefficients();

    double train_rmse = model.Evaluate("train.data");
    std::cout << "RMSE on training set = " << train_rmse << std::endl;

    double test_rmse = model.Evaluate("test.data");
    std::cout << "RMSE on test set = " << test_rmse << std::endl;

    return 0;
}
