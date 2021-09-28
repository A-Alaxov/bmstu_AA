#include "arr_gen.hpp"
#include <random>

void matr_gen(matrix &matr, int n, int m, int lim) {
    for (int i = 0; i < n; i++) {
        matr.push_back(vector<int>(m));
        for (int j = 0; j < m; j++) {
            matr[i][j] = rand() % lim;
        }
    }
}

int prepare(matrix &result, int n1, int m1, int n2, int m2) {
    if (m1 != n2) {
        return 1;
    }
    for (int i = 0; i < n1; i++) {
        result.push_back(vector<int>(m2, 0));
    }
    return 0;
}
