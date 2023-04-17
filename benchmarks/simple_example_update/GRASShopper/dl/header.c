#include "header.h"
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

DLNode * create_list(int size){
    DLNode * root = NULL;
    DLNode * tl = root;
    for(int i = 0; i < size; i++){
        DLNode * new_node = (DLNode *)malloc(sizeof(DLNode));
        new_node->next = NULL;
        new_node->prev = NULL;

        if(root == NULL){
            root = new_node;
            tl = new_node;
        }else{
            tl->next = new_node;
            new_node->prev = tl;
            tl = new_node;
        }
    }

    return root;
}
