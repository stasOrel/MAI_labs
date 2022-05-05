#ifndef MATRIX_H
#define MATRIX_H

#include "stdbool.h"


typedef struct Matrix {
    int CIP[100];
    int PI[100];
    int YE[100];
} Matrix;


void create_matrix(Matrix * m);
void input_matrix(Matrix * mat, int* n, int *m);
void print_matrix(Matrix *mat, int n, int m);
void function_matrix(Matrix * mat, int n, int m);

#endif