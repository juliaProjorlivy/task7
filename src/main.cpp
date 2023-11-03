#include "list.h"
#include "list_func.h"
#include "list_ctor_dtor.h"
#include "list_dump.h"
#include <stdio.h>

int main()
{
    size_t capacity = 20;
    struct list listt = {};
    list_ctor(&listt, capacity);
    for(int i = 1; i < 21; i++)
    {
        append(10 * i, &listt);
    }
    print_data(&listt);
    for(int i = 0; i < 17; i++)
    {
        printf("poped_%d = %d\n", i, *popend(&listt));
    }
    // elem_t *x = popend(&listt);
    // printf("x = %d\n", *x);
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

