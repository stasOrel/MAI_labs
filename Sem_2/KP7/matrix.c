#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#include "matrix.h"


void create_matrix(Matrix* m) {
    m = malloc(sizeof(Matrix));
}


void input_matrix(Matrix * mat, int *n, int *m) {
    FILE * input;
    input = fopen("input.mai", "r");
    if (input == NULL) {
        printf("Невозможно открыть файл\n");
        exit(1);
    }

    fscanf(input, "%d %d", n, m);
    int num;
    int cnt = 0;
    
    for (int i = 0; i != *n; ++i) {
        int flag = 0;
        for (int j = 0; j != *m; ++j) {
            fscanf(input, "%d", &num);
            if (num != 0) {
                if (flag == 0) {
                    flag = 1;
                    mat->CIP[i] = j + 1;
                }
                mat->PI[cnt] = j + 1;
                mat->YE[cnt] = num;
                cnt++;
            }
        }
        if (flag == 0)
            mat->CIP[i] = 0;
    }

    mat->PI[cnt] = 0;
    fclose(input);
}


void print_matrix(Matrix *mat, int n, int m) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(mat->PI[cnt] == j + 1) {
                int flag = 0;
                if (j + 1 == m) {
                    flag = 1;
                } else if (mat->PI[cnt] == mat->CIP[i + 1]) {
                    int k = cnt + 1;
                    int prevPI = mat->PI[cnt];
                    while(mat->PI[k] != 0) {
                        if (mat->PI[k] == mat->PI[cnt]) {
                            flag = 1;
                            break;
                        } else if (mat->PI[k] < prevPI) {
                            break;
                        }
                        k++;
                    }

                } else
                    flag = 1;
                if (flag > 0) {
                    printf("%d ", mat->YE[cnt]);
                    cnt++;
                } else
                    printf("0 ");
            }
            else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}


void function_matrix(Matrix * mat, int n, int m) {
    int n_nums[100];
    int n_cnt = 0;
    int max_len = 0;
    int n_sum[100];
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int local_len = 0;
        int local_sum = 0;
        for (int j = 0; j < m; ++j) {
            if(mat->PI[cnt] == j + 1) {
                int flag = 0;
                if (j + 1 == m) {
                    flag = 1;
                } else if (mat->PI[cnt] == mat->CIP[i + 1]) {
                    int k = cnt + 1;
                    int prevPI = mat->PI[cnt];
                    while(mat->PI[k] != 0) {
                        if (mat->PI[k] == mat->PI[cnt]) {
                            flag = 1;
                            break;
                        } else if (mat->PI[k] < prevPI) {
                            break;
                        }
                        k++;
                    }

                } else
                    flag = 1;
                if (flag > 0) {
                    local_len++;
                    local_sum += mat->YE[cnt];
                    cnt++;
                }
            }
        }
        if (local_len > max_len) {
            n_cnt = 1;
            max_len = local_len;
            n_sum[n_cnt - 1] = local_sum;
            n_nums[n_cnt - 1] = i + 1;
        } else if (local_len == max_len) {
            n_cnt++;
            n_sum[n_cnt - 1] = local_sum;
            n_nums[n_cnt - 1] = i + 1;          
        }
    }

    printf("Количество строк с минимальным числом 0-ых элементов: %d\n", n_cnt);
    for (int i = 0; i < n_cnt; ++i)
        printf("Строка №%d: сумма = %d\n", n_nums[i], n_sum[i]);
}