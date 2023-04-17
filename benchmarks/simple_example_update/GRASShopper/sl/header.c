#include "header.h"
#include <stdlib.h>

Node * create_list(int size){
    Node * root = NULL;
    Node * tl = root;
    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->next = NULL;
        if(root == NULL){
            root = new_node;
            tl = root;
        }else{
            tl->next = new_node;
            tl = new_node;
        }
    }

    return root;
}
