#include "algorithms.hpp"

int standart(matrix &result, matrix matr1, int n1, int m1, matrix matr2, int n2, int m2) {
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n2; k++) {
                result[i][j] = result[i][j] + matr1[i][k] * matr2[k][j];
            }
        }
    }
    return 0;
}

int vinograd(matrix &result, matrix matr1, int n1, int m1, matrix matr2, int n2, int m2) {
    vector<int> mulH(n1, 0);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1 / 2; j++) {
            mulH[i] = mulH[i] + matr1[i][j * 2] * matr1[i][j * 2 + 1];
        }
    }
    vector<int> mulV(n1, 0);
    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n2 / 2; j++) {
            mulV[i] = mulV[i] + matr2[j * 2][i] * matr2[j * 2 + 1][i];
        }
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            result[i][j] = -mulH[i] - mulV[j];
            for (int k = 0; k < n2 / 2; k++) {
                result[i][j] = result[i][j] + (matr1[i][2 * k + 1] + matr2[2 * k][j]) * (matr1[i][2 * k] + matr2[2 * k + 1][j]);
            }
        }
    }
    if (n2 % 2 == 1) {
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < m2; j++) {
                result[i][j] = result[i][j] + matr1[i][n2 - 1] * matr2[n2 - 1][j];
            }
        }
    }
    return 0;
}

int optimized_vinograd(matrix &result, matrix matr1, int n1, int m1, matrix matr2, int n2, int m2) {
    vector<int> mulH(n1, 0);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1 - 1; j += 2) {
            mulH[i] -= matr1[i][j] * matr1[i][j + 1];
        }
    }
    vector<int> mulV(n1, 0);
    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n2 - 1; j += 2) {
            mulV[i] -= matr2[j][i] * matr2[j + 1][i];
        }
    }
    bool flag = false;
    if (n2 % 2 == 1) {
        flag = true;
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            result[i][j] = mulH[i] + mulV[j];
            for (int k = 0; k < n2 - 1; k += 2) {
                result[i][j] += (matr1[i][k + 1] + matr2[k][j]) * (matr1[i][k] + matr2[k + 1][j]);
            }
            if (flag) {
                result[i][j] += matr1[i][n2 - 1] * matr2[n2 - 1][j];
            }
        }
    }
    return 0;
}
