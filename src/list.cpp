#include "list_func.h"
#include "verror.h"
#include "list_realloc.h"
#include <stdio.h>

const int decr_mul = 4;

int *append(elem_t value, struct list *listt, int *ret_val) // returns index of value in data
{
    if(listt->free == 0)
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
        listt->prev[0] = listt->tail;
        listt->next[0] = listt->free;
        int old_free = listt->free;
        listt->free = new_free;
        listt->prev[listt->free] = 0; ///
        (*ret_val) = old_free;

        return ret_val;
    }

    listt->n_elem++;
    listt->data[listt->free] = value;
    int new_free = listt->next[listt->free]; // index of next free cell
    listt->next[listt->free] = 0;   // the end of sequence

    listt->next[listt->tail] = listt->free; // the previouse end of sequence no more an end new cell is
    listt->prev[listt->free] = listt->tail;
    listt->tail = listt->free;
    listt->prev[0] = listt->tail;
    int old_free = listt->free;
    listt->free = new_free;
    listt->prev[listt->free] = 0; ///
    (*ret_val) = old_free;

    return ret_val;

}

int *insert(elem_t value, int index_before, struct list *listt, int *ret_val) // index_before in data not sequentially 
{
    if(index_before == listt->tail)
    {
        return append(value, listt, ret_val);
    }

    if(listt->free == 0)
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
        listt->next[0] = listt->head;
        int old_free = listt->free;
        listt->free = new_free;
        listt->prev[listt->free] = 0; ///
        (*ret_val) = old_free;

        return ret_val;
    }

    listt->n_elem++;
    listt->data[listt->free] = value;
    int new_free = listt->next[listt->free];

    listt->next[listt->free] = listt->next[index_before];
    listt->prev[listt->next[index_before]] = listt->free;
    listt->prev[listt->free] = index_before;
    listt->next[index_before] = listt->free;

    int old_free = listt->free;
    listt->free = new_free;

    listt->prev[listt->free] = 0; /// 
    (*ret_val) = old_free;

    return ret_val;
}

elem_t *popend(struct list *listt, int *ret_val)
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
    int old_tail = listt->tail;
    listt->tail = listt->prev[listt->tail];
    listt->next[listt->tail] = 0;
    listt->prev[0] = listt->tail;
    listt->prev[old_tail] = -1;
    listt->prev[listt->free] = 0; ///
    (*ret_val) = listt->data[listt->free];

    return ret_val;
}

elem_t *pop(int index, struct list *listt, int *ret_val) // del the element that contains in data in index cell
{
    if(index == listt->tail)
    {
        return popend(listt, ret_val);
    }

    if(listt->capacity >= listt->n_elem * decr_mul)
    {
        if(list_realloc(&listt, DECREASE))
        {
            VERROR_MEM;
            return NULL;
        }
    }

    if(index == listt->head)
    {
        listt->n_elem--;
        listt->next[0] = listt->next[index];
        listt->head = listt->next[index];
        listt->prev[listt->next[index]] = 0;
        listt->prev[index] = -1;
        listt->next[index] = listt->free;
        listt->free = index;
        
        listt->prev[listt->free] = 0; ///
        (*ret_val) = listt->data[index];
        return ret_val;
    }

    listt->n_elem--;
    listt->next[listt->prev[index]] = listt->next[index];
    listt->prev[listt->next[index]] = listt->prev[index];
    listt->prev[index] = -1;
    int new_free = index;
    listt->next[index] = listt->free;
    listt->free = new_free;
    listt->prev[listt->free] = 0; ///
    (*ret_val) = listt->data[index];

    return ret_val;
}

