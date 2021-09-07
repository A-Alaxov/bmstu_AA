#include "time_compare.hpp"
#include "levenstein.hpp"
#include "getCPUTime.hpp"
#include "string_gen.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void time_compare() {
    double start;
    double end;
    cout << setw(37) << "Time in ms" << endl;
    cout << setw(4) << "Len" << setw(15) << "Matrix" << setw(15) << "Recursion" << setw(15) << "With cache" << setw(15) << "Domerau" << endl;
    for (size_t j = 5; j < 15; j += 5) {
        string str1 = string_gen(j), str2 = string_gen(j);
        cout << setw(4) << j;
        start = getCPUTime();
        for (size_t i = 0; i < 10000; i++) {
            matr_method(str1, str2);
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / 10000;

        size_t n = 1;
        if (j == 5)
            n = 10000;
        start = getCPUTime();
        for (size_t i = 0; i < n; i++) {
            recur_method(str1, str1.length(), str2, str2.length());
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        start = getCPUTime();
        for (size_t i = 0; i < 10000; i++) {
            rec_cache_method(str1, str1.length(), str2, str2.length());
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / 10000;

        start = getCPUTime();
        for (size_t i = 0; i < 10000; i++) {
            Domerau_method(str1, str1.length(), str2, str2.length());
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / 10000 << endl;
    }
    size_t n = 10000;
    for (size_t j = 20; j < 60; j += 10) {
        string str1 = string_gen(j), str2 = string_gen(j);
        cout << setw(4) << j;
        start = getCPUTime();
        for (size_t i = 0; i < n; i++) {
            matr_method(str1, str2);
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        cout << setw(15) << "";

        start = getCPUTime();
        for (size_t i = 0; i < n; i++) {
            rec_cache_method(str1, str1.length(), str2, str2.length());
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        start = getCPUTime();
        for (size_t i = 0; i < n; i++) {
            Domerau_method(str1, str1.length(), str2, str2.length());
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / n << endl;
    }
}
