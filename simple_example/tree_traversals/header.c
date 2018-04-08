#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int rand_num(){
    return rand()%MAX_RAND;
}

TNode * insert(TNode * root, TNode * node){
    if(root == NULL)
        return node;

    if(rand_num() >= 0){
        if(root->left == NULL){
            root->left = node;
            return root;
        }else{
            root->left = insert(root->left, node);
        }
    }else{
        if(root->right == NULL){
            root->right = node;
            return root;
        }else{
            root->right = insert(root->right, node);
        }
    }
    return root;
}

TNode * create_tree(int size){
    TNode * root = NULL;
    for(int i = 0; i < size; i++){
        TNode * node = (TNode *)malloc(sizeof(TNode));
        node->left = NULL;
        node->right = NULL;
        node->key = rand_num();
        root = insert(root, node);
    }
    return root;
}
