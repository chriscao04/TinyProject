#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Matrix.hpp"
#include "Vector.h"
#include "LinearSystem.hpp"

using namespace std;

void load_data(const string& filename, vector<vector<double>>& features, vector<double>& targets) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<double> row;
        int col = 0;
        double vals[6];
        double prp = 0;
        int idx = 0;
        while (getline(ss, token, ',')) {
            if (col >= 2 && col <= 7) vals[idx++] = stod(token); 
            if (col == 8) prp = stod(token);
            col++;
        }
        features.push_back({vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]});
        targets.push_back(prp);
    }
}

int main() {
    vector<vector<double>> features;
    vector<double> targets;
    load_data("machine.data", features, targets);

    int N = features.size();
    int nTrain = N * 0.8;
    vector<int> indices(N);
    for (int i = 0; i < N; ++i) indices[i] = i;

    random_device rd;
    mt19937 g(rd());
    shuffle(indices.begin(), indices.end(), g);

    Matrix A(nTrain, 6);
    Vector b(nTrain);
    Matrix Atest(N - nTrain, 6);
    Vector btest(N - nTrain);

    for (int i = 0; i < nTrain; ++i) {
        for (int j = 0; j < 6; ++j)
            A(i+1, j+1) = features[indices[i]][j];
        b[i] = targets[indices[i]];
    }
    for (int i = nTrain; i < N; ++i) {
        for (int j = 0; j < 6; ++j)
            Atest(i-nTrain+1, j+1) = features[indices[i]][j];
        btest[i-nTrain] = targets[indices[i]];
    }

    Matrix AT(6, nTrain);
    for (int i = 1; i <= nTrain; ++i)
        for (int j = 1; j <= 6; ++j)
            AT(j, i) = A(i, j);

    Matrix ATA = AT * A;
    Vector ATb(6);
    for (int i = 1; i <= 6; ++i) {
        double sum = 0;
        for (int j = 0; j < nTrain; ++j)
            sum += AT(i, j+1) * b[j];
        ATb[i-1] = sum;
    }

    LinearSystem sys(ATA, ATb);
    Vector x = sys.Solve();

    //Test set
    double mse = 0;
    for (int i = 0; i < btest.size(); ++i) {
        double pred = 0;
        for (int j = 0; j < 6; ++j)
            pred += x[j] * Atest(i+1, j+1);
        mse += (pred - btest[i]) * (pred - btest[i]);
    }
    mse /= btest.size();
    double rmse = sqrt(mse);

    cout << "RMSE on test set: " << rmse << endl;
    return 0;
}