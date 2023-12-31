#include "list.h"
#include "list_realloc.h"
#include "verror.h"
#include <stdlib.h>

const int incr_mul = 2;

int list_realloc(struct list **listt, realloc_state state)
{
    if(state == INCREASE)
    {
        (*listt)->capacity *= incr_mul;
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
        
        for(size_t i = (size_t)((*listt)->tail) + 1; i <= (*listt)->capacity; i++)
        {
            (*listt)->data[i] = 0;
            (*listt)->next[i] = (int)i + 1;
            (*listt)->prev[i] = -1;
        }
    
        (*listt)->next[(*listt)->capacity] = 0;
        (*listt)->free = (*listt)->tail + 1;
        (*listt)->prev[0] = (*listt)->tail;

        (*listt)->prev[(*listt)->free] = 0; /// 

    }

    if(state == DECREASE)
    {
        (*listt)->capacity = (*listt)->capacity / 2;
        elem_t *new_data = (elem_t *)calloc(sizeof(elem_t), ((*listt)->capacity + 1)); // +1 for null cell and +1 for the empty cell at the end of new_data
        if(new_data == NULL)
        {
            VERROR_MEM;
            return 1;
        }

        int i_elem = (*listt)->head;
        for(size_t i = 1; i <= (*listt)->n_elem; i++)
        {
            new_data[i] = (*listt)->data[i_elem];
            i_elem = (*listt)->next[i_elem];

            (*listt)->next[i] = (int)i + 1;
            (*listt)->prev[i] = (int)i - 1;
        }
        new_data[0] = poison; //
        (*listt)->prev[0] = (int)(*listt)->n_elem; //
        (*listt)->next[0] = 1;

        int *new_next = (int *)realloc((*listt)->next, sizeof(int) * ((*listt)->capacity + 1));
        if(new_next == NULL)
        {
            VERROR_MEM;
            free(new_data);
            return 1;
        }
        (*listt)->next = new_next;

        int *new_prev = (int *)realloc((*listt)->prev, sizeof(int) * ((*listt)->capacity + 1));
        if(new_prev == NULL)
        {
            VERROR_MEM;
            free(new_data);
            free((*listt)->next);
            return 1;
        }
        (*listt)->prev = new_prev;

        for(size_t i = (*listt)->n_elem + 1; i <= (*listt)->capacity; i++)
        {
            (*listt)->next[i] = (int)i + 1; //
            (*listt)->prev[i] = -1;
        }

        (*listt)->next[(*listt)->capacity] = 0;
        (*listt)->free = (int)(*listt)->n_elem + 1;
        (*listt)->head = 1;
        (*listt)->tail = (int)((*listt)->n_elem);
        (*listt)->next[(*listt)->tail] = 0;
        (*listt)->next[(*listt)->capacity] = 0; ///
        
        (*listt)->prev[(*listt)->free] = 0; ///

        free((*listt)->data);
        (*listt)->data = new_data;
    }
    
    return 0;
}
