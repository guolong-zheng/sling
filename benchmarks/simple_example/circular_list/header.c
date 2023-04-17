#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

CNode * create_list(int size){
    CNode * hd = NULL;
    for(int i = 0; i < size; i++){
        CNode * newnode = (CNode *)malloc(sizeof(CNode));
        newnode->key = rand();
        if(hd == NULL){
            hd = newnode;
            hd->next = hd;
        }else{
            newnode->next = hd->next;
            hd->next = newnode;
        }
    }
    return hd;
}
