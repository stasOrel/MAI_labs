#include "stack_list.h"

int main() {
    Stack *st = stack_create();
    stack_pop(st);
    Stack *st2 = stack_create();
    stack_push(st2, 10);
    stack_push(st2, 8);
    stack_join(st2, st);
    print_stack(st2);
    print_stack(st2);
}
