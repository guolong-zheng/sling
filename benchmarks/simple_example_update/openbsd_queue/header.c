#include "header.h"
#include <stdio.h>
#include <stdlib.h>


Node * create_queue(int size){
    Node * hd = (Node *)malloc(sizeof(Node));
    hd->next = NULL;
    hd->last = hd;

    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->next = hd;
        new_node->last = hd->last;
        hd = new_node;
    }
    return hd;
}

Node * create_queue_buggy(int size){
    Node * hd = (Node *)malloc(sizeof(Node));
    hd->next = NULL;
    hd->last = hd;

    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->next = NULL;
        Node * lst = hd->last;
        lst->next = new_node;
        hd->last = new_node;
    }
    return hd;
}
