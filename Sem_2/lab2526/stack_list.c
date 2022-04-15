#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "stack_list.h"


Stack *stack_create()
{
    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;
    return s;
}


StackNode *insert_stack_node(StackNode *parent, Item value)
{
    StackNode *new_node = malloc(sizeof(StackNode));

    new_node->data = value;
    new_node->next = parent;

    return new_node;
}


void stack_push(Stack *s, Item value)
{
    s->head = insert_stack_node(s->head, value);
    s->size++;
}


Item stack_top(Stack *s) {
    if (s->head != NULL)
        return s->head->data;
    else
        printf("Стек пустой, невозможно выолнить top\n");
}


void stack_pop(Stack *s)
{
    if (s->head != NULL) {
        StackNode *tmp = s->head->next;
        free(s->head);
        s->head = tmp;
        s->size--;
    }
    else
        printf("Стек пустой, невозможно выолнить top\n");
}


bool stack_is_empty(Stack *s)
{
    return (s->head == NULL);
}


void stack_join(Stack  *a, Stack *b)
{
    struct stacknode *buttom_b = b->head;
    while (buttom_b->next != NULL)
        buttom_b = buttom_b->next;

    buttom_b->next = a->head;
    a->head = b->head;
    a->size += b->size;
}

void print_stack(Stack *s) {
    StackNode *s_node = s->head;

    while (s_node->next != NULL) {
        printf("%d ", s_node->data);
        s_node = s_node->next;
    }
    
    if (s->size > 0)
        printf("%d", s_node->data);
    printf("\n");
}
