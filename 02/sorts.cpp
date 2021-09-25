#include "sorts.hpp"

void swap(int *el1, int *el2)
{
    int temp = *el1;
    *el1 = *el2;
    *el2 = temp;
}

void bubble_sort(int* l, int* r) {
    for (int* j = r; j > l + 1; j--) {
        for (int* i = l; i < j - 1; i++) {
            if (*i > *(i + 1)) {
                swap(i, (i + 1));
            }
        }
    }
}

void selection_sort(int* l, int* r) {
    int min, *ind;
    for (int *i = l; i < r; i++) {
        min = *i;
        ind = i;
        for (int *j = i + 1; j < r; j++) {
            if (*j < min) {
                min = *j;
                ind = j;
            }
        }
        swap(i, ind);
    }
}

void gnome_sort(int* l, int* r) {
    int *i = l;
    while (i < r) {
        if (i == l || *(i - 1) <= *i)
            i++;
        else {
            swap((i - 1), i);
            i--;
        }
    }
}
