#include "arr_gen.hpp"
#include <random>

using namespace std;

void gen_best_case(int len, int *arr) {
    for (int i = 0; i < len; i++) {
        arr[i] = i;
    }
}

void gen_normal_case(int len, int *arr) {
    for (int i = 0; i < len; i++) {
        arr[i] = rand() % len;
    }
}

void gen_worst_case(int len, int *arr) {
    for (int i = 0; i < len; i++) {
        arr[i] = len - i - 1;
    }
}
