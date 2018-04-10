#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void simpleq_insert_tail(Node * head)
{
  //pre
  Node * elm = (Node *) malloc(sizeof(Node));
  elm->next = NULL;
  Node * lst = head->last;
  lst->next = elm;
  head->last = elm;
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * hd = create_queue(size);
    simpleq_insert_after(hd);
}
    return 0;
}
