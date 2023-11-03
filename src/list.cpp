#include "list_func.h"
#include "verror.h"
#include "list_realloc.h"
#include <stdio.h>

const int decr_mul = 4;

int *append(elem_t value, struct list *listt) // returns index of value in data
{
    if(listt->free == -1)
    {
        if(list_realloc(&listt, INCREASE))
        {
            VERROR_MEM;
            return NULL;
        }
    }
    if(listt->head == 0)
    {
        listt->head = listt->free;
        listt->n_elem++;
        listt->data[listt->free] = value;
        int new_free = listt->next[listt->free]; // index of next free cell
        listt->next[listt->free] = 0;

        listt->prev[listt->free] = listt->tail;
        listt->tail = listt->free;
        int *old_free = &(listt->free);
        listt->free = new_free;

        return old_free;
    }

    listt->n_elem++;
    listt->data[listt->free] = value;
    int new_free = listt->next[listt->free]; // index of next free cell
    listt->next[listt->free] = 0;   // the end of sequence

    listt->next[listt->tail] = listt->free; // the previouse end of sequence no more an end new cell is
    listt->prev[listt->free] = listt->tail;
    listt->tail = listt->free;
    int *old_free = &(listt->free);
    listt->free = new_free;

    return old_free;

}

int *insert(elem_t value, int index_before, struct list *listt) // index_before in data not sequentially 
{
    if(index_before == listt->tail)
    {
        return append(value, listt);
    }

    if(listt->free == -1)
    {
        if(list_realloc(&listt, INCREASE))
        {
            VERROR_MEM;
            return NULL;
        }
    }

    if(index_before == 0)
    {
        listt->n_elem++;
        listt->data[listt->free] = value;
        int new_free = listt->next[listt->free];

        listt->next[listt->free] = listt->head;
        listt->prev[listt->head] = listt->free;
        listt->prev[listt->free] = 0;
        listt->head = listt->free;
        int *old_free = &(listt->free);
        listt->free = new_free;

        return old_free;
    }

    listt->n_elem++;
    listt->data[listt->free] = value;
    int new_free = listt->next[listt->free];

    listt->next[listt->free] = listt->next[index_before];
    listt->prev[listt->next[index_before]] = listt->free;
    listt->prev[listt->free] = index_before;
    listt->next[index_before] = listt->free;

    int *old_free = &(listt->free);
    listt->free = new_free;

    return old_free;
}

elem_t *popend(struct list *listt)
{
    if(listt->capacity >= listt->n_elem * decr_mul)
    {
        if(list_realloc(&listt, DECREASE))
        {
            VERROR_MEM;
            return NULL;
        }
    }
    listt->n_elem--;
    listt->next[listt->tail] = listt->free;
    listt->free = listt->tail;
    listt->tail = listt->prev[listt->tail];

    return &(listt->data[listt->free]);
}

elem_t *pop(int index, struct list *listt) // del the element that contains in data in index cell
{
    if(index == listt->tail)
    {
        return popend(listt);
    }

    if(listt->capacity >= listt->n_elem * decr_mul)
    {
        if(list_realloc(&listt, DECREASE))
        {
            VERROR_MEM;
            return NULL;
        }
    }

    listt->n_elem--;
    listt->next[listt->prev[index]] = listt->next[index];
    listt->prev[listt->next[index]] = listt->prev[index];
    listt->prev[index] = -1;
    int new_free = listt->next[index];
    listt->next[index] = listt->free;
    listt->free = new_free;

    return &(listt->data[index]);
}

