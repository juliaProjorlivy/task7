#include "list_ctor_dtor.h"
#include "verror.h"
#include <stdlib.h>

int list_ctor(struct list *listt, size_t capacity)
{
    elem_t *check_data = (elem_t *)calloc(sizeof(elem_t), capacity + 1); // check if ok
    if(check_data == NULL)
    {
        VERROR_MEM;
        return 1;
    }

    int *check_next = (int *)calloc(sizeof(int), capacity + 1);
    if(check_next == NULL)
    {
        VERROR_MEM;
        free(check_data);
        return 1;
    }

    int *check_prev = (int *)calloc(sizeof(int), capacity + 1);
    if(check_prev == NULL)
    {
        VERROR_MEM;
        free(check_data);
        free(check_next);
        return 1;
    }
    
    listt->data = check_data;
    listt->next = check_next;
    listt->prev = check_prev;

    for(size_t i = 1; i <= capacity; i++)
    {
        listt->next[i] = (int)i+1;
        listt->prev[i] = -1; ////
    }
    listt->next[capacity] = 0;
    listt->data[0] = poison;
    listt->head = 0;
    listt->tail = 0;
    listt->free = 1;
    listt->prev[listt->free] = 0;
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



