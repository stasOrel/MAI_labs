#include <stdio.h>

#include "circular_list.h"


int main() {
    circular_list* l = create_list(); 

    append_list(l, 10);
    print_list(l);
    delete_list(l, 10);
    print_list(l);

    append_list(l, 1);
    append_list(l, 2);
    append_list(l, 3);
    append_list(l, 4);
    append_list(l, 5);
    print_list(l);
    // delete_list(l, 1);
    delete_list(l, 5);
    // delete_list(l, 3);
    print_list(l);

    insert_list(l, 1, 8);
    insert_list(l, 2022, 2022);
    print_list(l);
}