#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * create_node(int i)
{
    SNnode * node = (SNnode *)malloc(sizeof(SNnode));
    node->key = i;
    node->next = NULL;
    return node;
}

SNnode * create_sll(int size){
    int i;
    SNnode * root = NULL;
    for(i = 0; i < size; i++){
        root = sll_append_node(root, create_node(i));
    }

    return root;
}

SNnode * sll_append_node(SNnode * x1, SNnode * x2)
{
        if (x1 == NULL) {
                return x2;
        } else {
                SNnode * tmp = sll_append_node(x1->next, x2);
                x1->next = tmp;
                return x1;
        }
}
