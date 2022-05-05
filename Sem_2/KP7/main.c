#include <stdio.h>

#include "matrix.h"

int main() {
    int n;
    int m;
    Matrix* mat;
    create_matrix(mat);

    input_matrix(mat, &n, &m);
    printf("%d %d\n", n, m);
    print_matrix(mat, n, m);
    function_matrix(mat, n, m);
}