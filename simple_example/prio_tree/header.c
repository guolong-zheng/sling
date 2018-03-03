#include "prio_tree.h"
#include <stdio.h>
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND+1) - MAX_RAND;
}

BNode * create_tree(int size){
    BNode * root = NULL;
    for(int i = 0; i < size; i++){
        root = treap_insert_rec(root, (int)rand(), (int)rand());
    }

    return root;
}
