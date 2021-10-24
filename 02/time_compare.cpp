#include "time_compare.hpp"
#include "getCPUTime.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void time_compare(int init) {
    double start;
    double end;
    int repeats;
    cout << setw(33) << "Time in ms" << endl;
    cout << setw(3) << "Len" << setw(15) << "Standart" << setw(15) << "Vinograd" << setw(15) << "Optimized" << endl;
    for (int n = init; n < 1100; n += 100) {
        cout << setw(4) << n;
        if (n < 200) {
            repeats = 100;
        }
        else if (n < 300) {
            repeats = 50;
        }
        else {
            repeats = 5;
        }

        matrix matr1, matr2, result;
        matr_gen(matr1, n, n, RAND_MAX);
        matr_gen(matr2, n, n, RAND_MAX);
        prepare(result, n, n, n, n);

        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            standart(result, matr1, n, n, matr2, n, n);
        }
        end = getCPUTime();

        cout << setw(15) << (end - start) / repeats;
        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            vinograd(result, matr1, n, n, matr2, n, n);
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats;

        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            optimized_vinograd(result, matr1, n, n, matr2, n, n);
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats << endl;
    }
}
