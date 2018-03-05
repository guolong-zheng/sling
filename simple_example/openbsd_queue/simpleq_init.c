#include "openbsd_queue.h"
#include <stdlib.h>

void simpleq_init()
{
  //pre
  Node * head = (Node *) malloc(sizeof(Node));
  head->next = NULL;
  head->last = head;
  //post
}

int main(){
    simpleq_init();
    return 0;
}
