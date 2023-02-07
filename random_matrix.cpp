#include <iostream>
#include <random>
using namespace std;

void generateRandomMatrix(int N, double probabilityOfOne, int mat[N][N]) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dis(gen) < probabilityOfOne) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }
}
