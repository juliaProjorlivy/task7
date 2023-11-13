#include "list_dump.h"
#include "time.h"

void print_info(const char *filename, int n_line, const char *fucnname)
{
    FILE *file = fopen("graph_info.txt", "a");
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
    fprintf(file, "at %sin %s (%d): %s\n", asctime(info), filename, n_line, fucnname);

    fclose(file);
}

void print_graph(struct list *listt, const char *graph_name)
{
    printf("digraph %s{\n", graph_name);
    printf("\tlabel=\"%s\";\n", graph_name);

    printf("    rankdir=LR;\n");
    printf("    node[color=\"red\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightpink\"];\n");
    printf("    edge[color=\"deepskyblue\",fontsize=12];\n");
    printf("\tnode_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"];\n", 0, 0, listt->data[0], listt->next[0], listt->prev[0]);
    printf("    node_%d[color=\"blue\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightblue\"];\n", listt->next[0]);
    printf("\tnode_%d:<f0>->node_%d;\n", 0, listt->next[0]);

    int data_i = listt->next[0];
    while(listt->next[data_i] >= 0)
    {
        printf("    node[color=\"blue\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightblue\"];\n");
        printf("    edge[color=\"deepskyblue\",fontsize=12];\n");

        printf("\tnode_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"];\n", data_i, data_i, listt->data[data_i], listt->next[data_i], listt->prev[data_i]);
        printf("\tnode_%d:<f0>->node_%d;\n", data_i, listt->next[data_i]);

        if(listt->next[data_i] == 0) break;

        data_i = listt->next[data_i];
        
    }
    
    int free_i = listt->free;
    while(listt->next[free_i] >= 0)
    {
        printf("    node[color=\"darkgreen\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightgreen\"];\n");
        printf("    edge[color=\"seagreen\",fontsize=12];\n");

        printf("\tnode_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"];\n", free_i, free_i, listt->data[free_i], listt->next[free_i], listt->prev[free_i]);
        printf("\tnode_%d:<f0>->node_%d;\n", free_i, listt->next[free_i]);
        
        if(listt->next[free_i] == 0)
        {
            break;
        }

        free_i = listt->next[free_i];
    }

    int even_i = 0;
    while(even_i < (int)(listt->capacity))
    {
        printf("\tnode_%d->node_%d[weight=1000, color=\"white\"];\n", even_i, even_i + 1);
        even_i++;
    }

    printf("\tnode_0->node_%d;\n", listt->free);
    printf("    HEAD[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    TAIL[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    FREE[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    edge[color=\"magenta\",fontsize=12];\n");
    printf("\tHEAD->node_%d;\n", listt->head);
    printf("\tTAIL->node_%d;\n", listt->tail);
    printf("\tFREE->node_%d;\n", listt->free);

    printf("\tCAPACITY[shape=record, label=\"capacity: %zu\", color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"lightgrey\"];\n", listt->capacity);
    printf("\tN_ELEM[shape=record, label=\"n_elem: %zu\", color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"lightgrey\"];\n", listt->n_elem);
    printf("\tCAPACITY->node_0[weight=8, color=\"white\"];\n");
    printf("\tN_ELEM->node_0[weight=8, color=\"white\"];\n");

    printf("}\n");

}




