#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include "list.h"

int *append(elem_t value, struct list *listt);

int *insert(elem_t value ,int index_before, struct list *listt);

elem_t *popend(struct list *listt);

#endif
