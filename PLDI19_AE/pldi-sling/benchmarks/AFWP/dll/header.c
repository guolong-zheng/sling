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

DLNode * create_dll(int size){
    DLNode * root = NULL;
    int i = 0;
    for( i = 0; i < size; i++){
        DLNode * node = (DLNode *)malloc(sizeof(DLNode));
        node->next = NULL;
        node->prev = NULL;
        if(root == NULL)
            root = node;
        else{
            node->next = root;
            root->prev = node;
            root = node;
        }
    }
    return root;
}
