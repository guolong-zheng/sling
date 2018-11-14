#include "header.h"
#include <stdlib.h>

Node * create_list(int size){
    Node * root = NULL;
    for(int i = 0; i < size; i++){
        Node * node = (Node *)malloc(sizeof(Node));
        node->next = NULL;
        node->prev = NULL;
        if(root == NULL){
            root = node;
        }else{
            node->next = root;
            root->prev = node;
            root = node;
        }
    }
    return root;
}
