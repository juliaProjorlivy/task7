#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <limits.h>

static const int poison = INT_MAX;
typedef int elem_t;

struct list
{
    elem_t *data;
    int *next;
    int *prev;
    int head;
    int tail;
    int free;
    size_t capacity;
    size_t n_elem;
};



#endif
