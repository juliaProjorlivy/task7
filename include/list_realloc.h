#ifndef LIST_REALLOC_H
#define LIST_REALLOC_H

typedef enum 
{
    DECREASE = 0,
    INCREASE = 1,
} realloc_state;

int list_realloc(struct list **listt, realloc_state state);

#endif
