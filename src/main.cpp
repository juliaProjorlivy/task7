#include "list.h"
#include "list_func.h"
#include "list_ctor_dtor.h"
#include "list_dump.h"
#include "verror.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        VERROR("no needed file");
        return 1;
    }
    freopen(argv[1], "w", stdout);
    size_t capacity = 20;
    struct list listt = {};
    list_ctor(&listt, capacity);
    int ret_val = 0;
    int ind_2 = 0;
    
    // for(int i = 1; i < 3; i++)
    // {
    //     ind_2 = *append(10 * i, &listt, &ret_val);
    // }
    // int ind_3 = *append(777, &listt, &ret_val);
    // insert(444, ind_3, &listt, &ret_val);
    // for(int i = 1; i < 3; i++)
    // {
    //     append(i, &listt, &ret_val);
    // }
    // popend(&listt, &ret_val);
    // pop(ind_2, &listt, &ret_val);
    // pop(1, &listt, &ret_val);
    // insert(666, 3, &listt, &ret_val);

    printf("digraph{\n");
    print_graph_v3(&listt);
    printf("}\n");
    list_dtor(&listt);
    return 0;
}

