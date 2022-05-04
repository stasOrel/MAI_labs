#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "circular_list.h"


circular_list* create_list()
{
    circular_list* l = malloc(sizeof(circular_list));
    l->genesis_item = malloc(sizeof(list_item));
    l->genesis_item->prev = l->genesis_item;
    l->genesis_item->next = l->genesis_item;
    l->genesis_item->val = 1991;
    l->size = 0;
    return l;
}


void append_list(circular_list* l, int val) {
    if (l->size == 0)
        l->genesis_item->val = val;
    else {
        list_item* new_item = malloc(sizeof(list_item));
        new_item->val = val;
        new_item->next = l->genesis_item;
        if (l->size > 1) {
            new_item->prev = l->genesis_item->prev;
            l->genesis_item->prev->next = new_item;
        }
        else
            new_item->prev = l->genesis_item;
        l->genesis_item->prev = new_item;
        if (l->size == 1)
            l->genesis_item->next = new_item;
    }
    l->size++;
}


void insert_list(circular_list* l, int index, int val) {
    if (index >= l->size - 1) {
        append_list(l, val);
        return;
    }

    list_item* item = l->genesis_item;
    for (int i = 0; i < size_of_list(l); ++i) {
        if (i == index) {
            list_item* new_item = malloc(sizeof(list_item));
            new_item->val = val;
            new_item->prev = item;
            new_item->next = item->next;
            item->next->prev = new_item;
            item->next = new_item;
            l->size++;
            break;           
        }
        item = item->next;
    }
}


void delete_list(circular_list* l, int val) {
    list_item* item = l->genesis_item;
    for (int i = 0; i < l->size; ++i) {
        if (item->val == val) {
            if (item == l->genesis_item && l->size == 1) {
                l->size = 0;
                item->val = 1991;
            } else {
                item->prev->next = item->next;
                item->next->prev = item->prev;
                if (item == l->genesis_item) {
                    l->genesis_item = item->next;
                }
                l->size--;
                free(item);
            }
            break;
        }
        item = item->next;
    }
}


void print_list(circular_list* l) {
    int size = l->size;
    list_item* item = l->genesis_item;
    for (int i = 0; i < size; ++i) {
        printf("%d ", item->val);
        item = item->next;
    }
    printf("\n");
}


int size_of_list(circular_list* l) {
    return l->size;
}


void dopolnenie(circular_list* l, int val, int k) {
    if (size_of_list(l) >= k)
        return;
    else
        for (int i = size_of_list(l); i < k; ++i)
            append_list(l, val);
}