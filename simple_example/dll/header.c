#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int rand_num(){
    return rand()%(2*MAX_RAND) - MAX_RAND;
}

DLNode * create_node(){
    DLNode * node = (DLNode *)malloc(sizeof(DLNode));
    node->key = rand_num();
    node->next = NULL;
    node->prev = NULL;

    return node;
}

DLNode * create_dll(int size){
    DLNode * root = NULL;
    int i = 0;
    for(i = 0; i < size; i++){
        DLNode * node = create_node();
        root = dll_append_node(root, node);
    }

    return root;
}

DLNode * dll_append_node(DLNode * x1, DLNode * x2)
{
   if (x1 == NULL) {
     return x2;
   } else {
     DLNode * tmp = dll_append_node(x1->next, x2);
     x1->next = tmp;
     if (tmp) tmp->prev = x1;
     return x1;
   }
}
