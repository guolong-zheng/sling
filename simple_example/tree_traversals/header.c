#include "header.h"
#include <stdlib.h>

int rand_num(){
    return rand()%2 - 2;
}

TNode * create_node(){
    TNode * node = (TNode *)malloc(sizeof(TNode));
    node->left = NULL;
    node->right = NULL;
    node->key = 0;
}

TNode * insert(TNode * root, TNode * node){
    if(root == NULL)
        return node;
    else if(rand_num()){
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

}

TNode * create_tree(int size){
    TNode * root = NULL;
    for(int i = 0; i < size; i++){
        node = crate_node();
        root = insert(root, node);
    }
    return root;
}
