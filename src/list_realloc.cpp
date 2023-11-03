#include "list.h"
#include "list_realloc.h"
#include "verror.h"
#include <stdlib.h>


int list_realloc(struct list **listt)
{
    (*listt)->capacity *= 2;
    elem_t *new_data = (elem_t *)realloc((*listt)->data, sizeof(elem_t) * ((*listt)->capacity + 1));
    if(new_data == NULL)
    {
        VERROR_MEM;
        return 1;
    }
    (*listt)->data = new_data;

    int *new_next = (int *)realloc((*listt)->next, sizeof(int) * ((*listt)->capacity + 1));
    if(new_next == NULL)
    {
        VERROR_MEM;
        return 1;
    }
    (*listt)->next = new_next;

    int *new_prev = (int *)realloc((*listt)->prev, sizeof(int) * ((*listt)->capacity + 1));
    if(new_prev == NULL)
    {
        VERROR_MEM;
        return 1;
    }
    (*listt)->prev = new_prev;
    
    for(size_t i = (*listt)->n_elem + 1; i <= (*listt)->capacity; i++)
    {
        (*listt)->next[i] = (int)i + 1;
        (*listt)->prev[i] = (int)i;
    }
    (*listt)->prev[(*listt)->n_elem + 1] = (*listt)->tail;
    (*listt)->next[(*listt)->capacity] = -1;
    (*listt)->free = (int)((*listt)->n_elem) + 1;


    return 0;
}
