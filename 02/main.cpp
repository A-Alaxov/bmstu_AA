#include <iostream>
#include <string>
#include "time_compare.hpp"

int main() {
    int n = 3;
    matrix matr1, matr2, result;
    matr_gen(matr1, n, n, 5);
    matr_gen(matr2, n, n, 5);
    prepare(result, n, n, n, n);

    cout << "Matrix 1:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matr1[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "Matrix 2:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matr2[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "Classic algorithm:" << endl;
    standart(result, matr1, n, n, matr2, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "Vinograd algorithm:" << endl;
    vinograd(result, matr1, n, n, matr2, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "Optimized vinograd algorithm:" << endl;
    optimized_vinograd(result, matr1, n, n, matr2, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl << "Results for even sizes:" << endl;
    time_compare(100);

    cout << endl << "Results for not even sizes:" << endl;
    time_compare(101);
    return 0;
}
