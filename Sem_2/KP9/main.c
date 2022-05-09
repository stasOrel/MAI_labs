#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct data_st
{
    int key;
    char value[256];
} data_st;

void swap(data_st *a, data_st*b) {
    data_st temp = *a;
    *a = *b;
    *b = temp;
}

//O(n^(3/2))
void shell_sort(data_st data[256], int input_size, int reversed) { // 1: min -> ... -> max | -1: max -> ... -> min
    int step = input_size / 2;
    while (step >= 0) {
        for (int i = 0; i + step < input_size; ++i) {
            int ind = i + step;
            while(ind >= i + step && data[ind].key * reversed < data[ind - step].key * reversed) {
                swap(&data[ind - step], &data[ind]);
                ind -= step;
            }            
        }
        step--;
    }
}


void print_struct(data_st data[256], int input_size) {
    for (int i = 0; i < input_size; ++i)
        printf("%d %s", data[i].key, data[i].value);
}


void vector_shuffle(data_st data[256], int input_size) {
    long long step = time(NULL) % 4 + 1;
    for (long long i = step; i < input_size; ++i) {
        long long ind = i;
        while (ind >= step) {
            swap(&data[ind - step], &data[ind]);
            ind -= step;
        }
    }

    step = (time(NULL) / 83 * 56 + 215) % 2 + 1;
    for (long long i = step; i < input_size; ++i) {
        long long ind = i;
        while (ind >= step) {
            swap(&data[ind - step], &data[ind]);
            ind -= step;
        }
    }

    step = (time(NULL) / 15 * 9 + 20) % 3 + 1;
    for (long long i = step; i < input_size; ++i) {
        long long ind = i;
        while (ind >= step) {
            swap(&data[ind - step], &data[ind]);
            ind -= step;
        }
    }
}

int main() {
    FILE * f_values;
    f_values = fopen("input.values", "r");
    if (f_values == NULL) {
        printf("Невозможно открыть файл\n");
        exit(1);
    }

    FILE * f_keys;
    f_keys = fopen("input.keys", "r");
    if (f_keys == NULL) {
        printf("Невозможно открыть файл\n");
        exit(1);
    }


    data_st data[256];
    int input_size = 0;
    while (fscanf(f_keys, "%d", &data[input_size].key) == 1) { 
        fgets(data[input_size].value, 256, f_values);
        input_size++;
    }

    fclose(f_keys);
    fclose(f_values);

    printf("1.) Элементы упорядочены:\n\n");
    print_struct(data, input_size);
    printf("\n");

    printf("1.) Результат сортировки:\n\n");
    shell_sort(data, input_size, 1);
    print_struct(data, input_size);
    printf("\n");

    printf("2.) Элементы упорядочены в обратном порядке:\n\n");
    shell_sort(data, input_size, -1);
    print_struct(data, input_size);
    printf("\n");

    printf("2.) Результат сортировки:\n\n");
    shell_sort(data, input_size, 1);
    print_struct(data, input_size);
    printf("\n");

    printf("3.) Элементы не упорядочены:\n\n");
    vector_shuffle(data, input_size);
    print_struct(data, input_size);
    printf("\n");

    printf("3.) Результат сортировки:\n\n");
    shell_sort(data, input_size, 1);
    print_struct(data, input_size);
    printf("\n");
}