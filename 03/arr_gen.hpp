#ifndef INC_01_STRING_GEN_HPP
#define INC_01_STRING_GEN_HPP

typedef void (*gen_func_t)(int, int*);

void gen_best_case(int len, int *arr);

void gen_normal_case(int len, int *arr);

void gen_worst_case(int len, int *arr);

#endif
