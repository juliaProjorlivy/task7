#ifndef LIST_DUMP_H
#define LIST_DUMP_H

#include "list.h"

void print_next(struct list *listt);

void print_data(struct list *listt);

void print_prev(struct list *listt);

void print_graph(struct list *listt);

void print_graph_v2(struct list *listt);

void print_graph_v3(struct list *listt, const char *graph_name);

void print_graph_v4(struct list *listt, const char *graph_name = "GRAPH");

#endif
