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

void print_graph(struct list *listt)
{
    printf("    rankdir=LR;\n");
    printf("    node[color=\"blue\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightblue\"];\n");
    printf("    edge[color=\"deepskyblue\",fontsize=12];\n");
    printf("    node_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"]", 0, 0, listt->data[0], listt->next[0], listt->prev[0]);
    printf("    node_%d:<f0>->node_%d;\n", 0, listt->head);
    printf("    node_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"]", listt->head, listt->head, listt->data[listt->head], listt->next[listt->head], listt->prev[listt->head]);
    printf("    node_%d:<f0>->node_%d", listt->head, listt->next[listt->head]);
    int next = listt->next[listt->head];
    for(size_t i = 2; i <= listt->n_elem; i++)
    {
        printf("    node_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"]\n", next, next, listt->data[next], listt->next[next], listt->prev[next]);
        if(listt->next[next] != -1)
        {

        }
        printf("    node_%d:<f0>->node_%d\n", next, listt->next[next]);
        next = listt->next[next];
    }
}

void print_graph_v2(struct list *listt)
{
    printf("    rankdir=LR;\n");
    printf("    node[color=\"red\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightpink\"];\n");
    printf("    edge[color=\"deepskyblue\",fontsize=12];\n");
    printf("\tnode_%d[shape=record, label=\" №%d | <f0> val: %d\\nnext: %d\\nprev: %d\"];\n", 0, 0, listt->data[0], listt->next[0], listt->prev[0]);
    printf("    node_%d[color=\"blue\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightblue\"];\n", listt->next[0]);
    printf("\tnode_%d:<f0>->node_%d;\n", 0, listt->next[0]);
    for(size_t i = 1; i <= listt->capacity; i++)
    {
        if(listt->prev[i] == -1 || listt->free == (int)i)
        {
            printf("    node[color=\"darkgreen\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightgreen\"];\n");
            printf("    edge[color=\"seagreen\",fontsize=12];\n");
        }
        else
        {
            printf("    node[color=\"blue\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightblue\"];\n");
            printf("    edge[color=\"deepskyblue\",fontsize=12];\n");
        }
        printf("\tnode_%zu[shape=record, label=\" №%zu | <f0> val: %d\\nnext: %d\\nprev: %d\"];\n", i, i, listt->data[i], listt->next[i], listt->prev[i]);
        printf("\tnode_%zu:<f0>->node_%d;\n", i, listt->next[i]);

    }

    printf("\tnode_0->node_%d;\n", listt->free);
    printf("    HEAD[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    TAIL[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    FREE[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    edge[color=\"magenta\",fontsize=12];\n");
    printf("\tHEAD->node_%d;\n", listt->head);
    printf("\tTAIL->node_%d;\n", listt->tail);
    printf("\tFREE->node_%d;\n", listt->free);


}

void print_graph_v3(struct list *listt, const char *graph_name)
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

    printf("\tnode_0->node_%d;\n", listt->free);
    printf("    HEAD[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    TAIL[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    FREE[color=\"black\", frontsize=14, shape=\"rectangle\", style=\"filled\", fillcolor=\"hotpink\"];\n");
    printf("    edge[color=\"magenta\",fontsize=12];\n");
    printf("\tHEAD->node_%d;\n", listt->head);
    printf("\tTAIL->node_%d;\n", listt->tail);
    printf("\tFREE->node_%d;\n", listt->free);

    printf("}\n");

}

void print_graph_v4(struct list *listt, const char *graph_name)
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
        printf("\tnode_%d->node_%d[weight=10, color=\"white\"];\n", even_i, even_i + 1);
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

    printf("}\n");

}




