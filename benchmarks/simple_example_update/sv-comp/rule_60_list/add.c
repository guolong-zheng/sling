#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * list_add(struct list_head * elem, struct list_head * head)
{
    //pre
    struct list_head * next = head->next;
    elem->next = NULL;
    elem->prev = NULL;
    head->next = elem;
    elem->prev = head;
    elem->next = next;
    next->prev = elem;
    //post
    return head;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * hd = create_list(size);
    Node * elem = (Node *)malloc(sizeof(Node));
    elem->next = NULL;
    elem->prev = NULL;
    list_add(elem, hd);
    return 0;
}
