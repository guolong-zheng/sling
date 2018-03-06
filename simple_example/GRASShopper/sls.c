#include "sls.h"

Node * create_list(int init, int size){
    Node * root = NULL;
    Node * tl = root;
    int i = 0;
    for(i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->key = init + i;
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

Node * create_random(int size){
    Node * root = NULL;
    Node * tl = root;
    int i = 0;
    for(i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->key = rand()%10;
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
