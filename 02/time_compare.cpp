#include "time_compare.hpp"
#include "getCPUTime.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void time_compare(gen_func_t gen_func) {
    double start;
    double end;
    double copy;
    int repeats = 1000000;
    cout << setw(33) << "Time in ms" << endl;
    cout << setw(3) << "Len" << setw(15) << "Bubble" << setw(15) << "Selection" << setw(15) << "Gnome" << endl;
    for (int len = 10; len < 100; len += 10) {
        cout << setw(3) << len;

        int *arr = new int[len], *arr_copy = new int[len];
        gen_func(len, arr);
        memcpy(arr_copy, arr, len * sizeof(int));

        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        copy = (end - start) / repeats;

        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            bubble_sort(arr_copy, arr_copy + len);
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats - copy;

        memcpy(arr_copy, arr, len * sizeof(int));
        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            selection_sort(arr_copy, arr_copy + len);
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats - copy;

        memcpy(arr_copy, arr, len * sizeof(int));
        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            gnome_sort(arr_copy, arr_copy + len);
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats - copy << endl;

        delete[] arr;
        delete[] arr_copy;
    }
    repeats = 100000;
    for (int len = 100; len < 600; len += 100) {
        cout << setw(3) << len;

        int *arr = new int[len], *arr_copy = new int[len];
        gen_func(len, arr);
        memcpy(arr_copy, arr, len * sizeof(int));

        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        copy = (end - start) / repeats;

        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            bubble_sort(arr_copy, arr_copy + len);
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats - copy;

        memcpy(arr_copy, arr, len * sizeof(int));
        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            selection_sort(arr_copy, arr_copy + len);
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats - copy;

        memcpy(arr_copy, arr, len * sizeof(int));
        start = getCPUTime();
        for (int i = 0; i < repeats; i++) {
            gnome_sort(arr_copy, arr_copy + len);
            memcpy(arr_copy, arr, len * sizeof(int));
        }
        end = getCPUTime();
        cout << setw(15) << (end - start) / repeats - copy << endl;

        delete[] arr;
        delete[] arr_copy;
    }
}
