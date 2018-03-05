#include "header.h"
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

Node * create_list(int size){
    Node * root = NULL;
    Node * pos = root;
    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->key = (int)rand();
        new_node->next = NULL;
        if(root == NULL){
            root = new_node;
            pos = root;
        }else{
            pos->next = new_node;
            pos = new_node;
        }
    }
    return root;
}
