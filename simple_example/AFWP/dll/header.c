#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Node * create_sll(int size){
    Node * root = NULL;
    int i = 0;
    for(i = 0; i < size; i++){
        Node * node = (Node *)malloc(sizeof(Node));
        node->next = NULL;
        if(root == NULL)
            root = node;
        else{
            node->next = root;
            root = node;
        }
    }
    return root;
}
