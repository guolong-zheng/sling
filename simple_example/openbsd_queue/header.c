#include "header.h"

Node * create_queue(int size){
    Node * hd = (Node *)malloc(sizeof(Node));
    hd->next = NULL;
    hd->last = hd;

    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->next = NULL;
        Node * lst = head->last;
        lst->next = new_node;
        head->last = new_node;
    }

    return hd;
}
