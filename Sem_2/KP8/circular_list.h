#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct list_item {
    int val;
    struct list_item* next;
    struct list_item* prev;
} list_item;


typedef struct circular_list {
    list_item* genesis_item;
    int size;
} circular_list;


circular_list* create_list();
void append_list(circular_list* l, int val);
void insert_list(circular_list* l, int index, int val);
void delete_list(circular_list* l, int val);
void dopolnenie(circular_list* l, int val, int k);
int size_of_list(circular_list* l);
void print_list(circular_list* l);

#endif
