#ifndef INC_01_SORTS_HPP
#define INC_01_SORTS_HPP

#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

int standart(matrix &result, matrix matr1, int n1, int m1, matrix matr2, int n2, int m2);

int vinograd(matrix &result, matrix matr1, int n1, int m1, matrix matr2, int n2, int m2);

int optimized_vinograd(matrix &result, matrix matr1, int n1, int m1, matrix matr2, int n2, int m2);

#endif
