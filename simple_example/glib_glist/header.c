#include "header.h"
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

DLNode * create_list(int size){
    DLNode * hd = NULL;
    DLNode * tl = hd;
    for(int i = 0; i < size; i++){
        DLNode * new_node = (DLNode *)malloc(sizeof(DLNode));
        new_node->key = rand_num();
        new_node->next = NULL;
        new_node->pre = NULL;
        if(hd == NULL){
            hd = new_node;
            hd->next = hd;
            hd->pre = hd;
            tl = hd;
        }else{
            new_node->pre = tl;
            new_node->next = hd;
            hd->pre = new_node;
            tl->next = new_node;
            tl = new_node;
        }
    }

    return hd;
}
