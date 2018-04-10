#include <stdio.h>
#include <stdlib.h>

/*
pred lseg(head, tail) := emp & head=tail
        \/ (exists n. head->node{n,tail} * lseg(n,tail));
*/
typedef struct node {
  struct node * next;
  struct node * last;
} Node;

Node * create_queue1(int size);

Node * create_queue1(int size){
    //pre
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
    //post
    return hd;
}

Node * create_queue2(int size){
    //pre
    Node * hd = (Node *)malloc(sizeof(Node));
    hd->next = NULL;
    hd->last = hd;

    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->next = hd;
        new_node->last = hd->last;
        hd = new_node;
    }
    //post
    return hd;
}

int main(){
    //create_queue1(5);
    create_queue2(5);
    return 0;
}
