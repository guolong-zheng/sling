#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

BNode * create_tree(int size)
{
    BNode * root = NULL;
    int key;
    for(int i = 0; i < size; i++){
        key = rand_num();
        root = bst_insert_rec(key);
    }
    return root;
}
