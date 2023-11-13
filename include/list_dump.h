#ifndef LIST_DUMP_H
#define LIST_DUMP_H

#include "list.h"

void print_graph(struct list *listt, const char *graph_name = "GRAPH");

void print_info(const char *filename, int n_line, const char *fucnname);

#define LIST_DUMP(listt, graph_name)    \
        print_graph(listt, graph_name); \
        print_info(__FILE__, __LINE__, __func__)

#endif
