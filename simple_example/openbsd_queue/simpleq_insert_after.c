#include "openbsd_queue.h"
#include <stdlib.h>

void simpleq_insert_after(Node * head, Node * listelm)
{
  //pre
  Node * elm = (Node *) malloc(sizeof(Node));
  Node * lenn = listelm->next;
  elm->next = lenn;
  if (lenn == NULL) {
    head->last = elm;
  }
    listelm->next = elm;
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * hd = create_queue(size);
    Node * elm = hd->next;
    simpleq_insert_after(hd,elm);
    return 0;
}
