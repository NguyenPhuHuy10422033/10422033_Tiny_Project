#include "LinearRegression.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>

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
     std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)) + rand());
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
    const int runs = 30;
    double total_train_rmse = 0.0;
    double total_test_rmse = 0.0;

    for (int i = 0; i < runs; ++i) {
        ShuffleAndSplit("machine.data", "train.data", "test.data");

        LinearRegression model;
        model.LoadDataFromCSV("train.data");
        model.Train();

        double train_rmse = model.Evaluate("train.data");
        double test_rmse = model.Evaluate("test.data");

        total_train_rmse += train_rmse;
        total_test_rmse += test_rmse;

        std::cout << "Run " << (i + 1) << ": "
                  << "Train RMSE = " << train_rmse
                  << ", Test RMSE = " << test_rmse << std::endl;
    }

    std::cout << "Average Train RMSE: " << (total_train_rmse / runs) << std::endl;
    std::cout << "Average Test RMSE: " << (total_test_rmse / runs) << std::endl;

    return 0;
}
