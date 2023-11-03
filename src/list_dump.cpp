#include "list_dump.h"

void print_data(struct list *listt)
{
    printf("data:\n");
    printf("%d) %d\n", 0, listt->data[0]);
    printf("%d) %d\n", 1, listt->data[listt->head]);
    int next = listt->next[listt->head];
    for(size_t i = 2; i <= listt->n_elem; i++)
    {
        printf("%zu) %d\n", i, listt->data[next]);
        next = listt->next[next];
    }
    printf("---------\n");
}

void print_next(struct list *listt)
{
    printf("next:\n");
    for(size_t i = 0; i < listt->capacity; i++)
    {
        printf("%zu) %d\n", i, listt->next[i]);
    }
    printf("---------\n");
}

void print_prev(struct list *listt)
{
    printf("prev:\n");
    for(size_t i = 0; i < listt->capacity; i++)
    {
        printf("%zu) %d\n", i, listt->prev[i]);
    }
    printf("---------\n");
}

