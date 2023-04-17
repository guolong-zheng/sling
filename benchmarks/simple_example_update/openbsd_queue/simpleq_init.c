#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void simpleq_init()
{
  //pre
  Node * head = (Node *) malloc(sizeof(Node));
  head->next = NULL;
  head->last = head;
  //post
}

int main(int argc, char * argv[]){
    simpleq_init();
    return 0;
}
