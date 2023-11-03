#include "list_ctor_dtor.h"
#include <stdlib.h>
#include <limits.h>

const int poison = INT_MAX;

int list_ctor(struct list *listt, size_t capacity)
{
    listt->data = (elem_t *)calloc(sizeof(elem_t), capacity + 1); // check if ok
    listt->next = (int *)calloc(sizeof(int), capacity + 1);
    listt->prev = (int *)calloc(sizeof(int), capacity + 1);
    for(size_t i = 1; i <= capacity; i++)
    {
        listt->next[i] = (int)i+1;
        listt->prev[i] = (int)i;
    }
    listt->next[capacity] = -1;
    listt->data[0] = poison;
    listt->head = 0;
    listt->tail = 0;
    listt->free = 1;
    listt->capacity = capacity;
    listt->n_elem = 0;

    return 0;
}

int list_dtor(struct list *listt)
{
    free(listt->data);
    free(listt->next);
    free(listt->prev);
    listt->data = NULL;
    listt->next = NULL;
    listt->prev = NULL;

    return 0;
}



