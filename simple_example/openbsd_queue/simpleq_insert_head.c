#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void simpleq_insert_head(Node * head)
{
  //pre
  Node * elm = (Node *) malloc(sizeof(Node));
  elm->next = NULL;
  if (head->next == NULL) {
    head->last = elm;
  }
  head->next = elm;
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * hd = create_queue_buggy(size);
    simpleq_insert_head(hd);
    simpleq_insert_head(NULL);
    simpleq_insert_head(hd);
    return 0;
}
