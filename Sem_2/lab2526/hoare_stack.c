#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "stack_list.h"


typedef struct
{
    StackNode *l;
    StackNode *r;
} Pivot_lr;


Pivot_lr partition(Stack *st, StackNode *low, StackNode *high)
{
	StackNode *pivot = low;
	StackNode *i = NULL;
    StackNode *j = high;
    StackNode *right_pivot;

    while (j != NULL) {
        if (j->next == low) {
            right_pivot = j;
        }

        if (j->data <= pivot->data) {
            if (i == NULL)
                i = high;
            else
                i = i->next;

            int temp_data = i->data;
            i->data = j->data;
            j->data = temp_data;
            j = j->next;
        } else  {
            j = j->next;
        }
    }

    Pivot_lr ret;
    ret.l = pivot->next;
    ret.r = right_pivot;

    return ret;
}


int stack_len(StackNode *l, StackNode *r) {
    int cnt = 1;
    while (r != l) {
        cnt++;
        r = r->next;
    }
    return cnt;
}


void quickSort(Stack *st, StackNode *low, StackNode *high)
{
	if (low != high)
	{
        Pivot_lr pivot_lr = partition(st, low, high);

        if (pivot_lr.l != NULL) {
            int size = stack_len(pivot_lr.l, low);
            quickSort(st, pivot_lr.l, low);
        }
        if (pivot_lr.r != NULL) {
            int size = stack_len(pivot_lr.r, high);
            quickSort(st, pivot_lr.r, high);
        }
	}
}


int main() {
    Stack *st = stack_create();
    stack_push(st, 7);
    stack_push(st, 0); 
    stack_push(st, -4);
    stack_push(st, 3);
    stack_push(st, 1);
    stack_push(st, -2);
    stack_push(st, -5);
    
    StackNode *buttom_st = st->head;
    while (buttom_st->next != NULL) {
        buttom_st = buttom_st->next;
    }

    quickSort(st, buttom_st, st->head);
    print_stack(st);
}