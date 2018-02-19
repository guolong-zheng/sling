#include "create_tree.h"
#include <stdlib.h>

TNode * insert(TNode * root, int key){
    if(root == NULL){
        TNode * newnode = (TNode *)malloc(sizeof(TNode));
        newnode->key = key;
        newnode->right = NULL;
        newnode->left = NULL;
        root = newnode;
    }else if(key < root->key){
        root->left = insert(root, key);
    }else if(key > root->key){
        root->right = insert(root, key);
    }
    return root;
}

int get_key(TNode * root, int n){
    if(root == NULL)
        return 0;
    if(root->left == NULL)
        root->key = n + 1;
    else
        root->key = get_key(root->left, n) + 1;

    if(root->right == NULL)
        return n;
    else
        return get_key(root->right, n+1);
}

int get_order(TNode * root){

}

int get_size(TNode * root){}

TNode * create_tree(int size){
    TNode * root = NULL;
    for(int i = 0; i < size; i++)
        root = insert(root, (int)rand());


    return root;
}
