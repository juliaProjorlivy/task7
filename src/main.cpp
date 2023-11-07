#include "list.h"
#include "list_func.h"
#include "list_ctor_dtor.h"
#include "list_dump.h"
#include "verror.h"
#include <stdio.h>

int main()
{
    freopen("graph/graph.dot", "w", stdout);

    size_t capacity = 20;
    struct list listt = {};
    int ret_val = 0;
    int ind_2 = 0;

    list_ctor(&listt, capacity);
    
    for(int i = 1; i < 3; i++)
    {
        ind_2 = *append(10 * i, &listt, &ret_val);
    }
    int ind_3 = *append(777, &listt, &ret_val);
    insert(444, ind_3, &listt, &ret_val);
    print_graph_v4(&listt, "first_first");
    for(int i = 1; i < 3; i++)
    {
        append(i, &listt, &ret_val);
    }

    popend(&listt, &ret_val);
    print_graph_v4(&listt, "middle_one_3");
    pop(ind_2, &listt, &ret_val);
    print_graph_v4(&listt, "middle_4");
    pop(1, &listt, &ret_val);
    insert(666, 3, &listt, &ret_val);
    pop(3, &listt, &ret_val);

    print_graph_v4(&listt, "last");

    list_dtor(&listt);

    return 0;
}

