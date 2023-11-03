#include "list.h"
#include "list_func.h"
#include "list_ctor_dtor.h"
#include "list_dump.h"
#include <stdio.h>

int main()
{
    size_t capacity = 2;
    struct list listt = {};
    list_ctor(&listt, capacity);
    append(22, &listt);
    append(33, &listt);
    insert(111, 2, &listt);
    insert(222, 0, &listt);
    elem_t *x = popend(&listt);
    printf("x = %d\n", *x);
    print_data(&listt);
    print_next(&listt);
    print_prev(&listt);
    for(size_t i = 0; i  <= listt.capacity; i++)
    {
        printf("%zu) %d\n", i, listt.data[i]);
    }
    list_dtor(&listt);
    return 0;
}

