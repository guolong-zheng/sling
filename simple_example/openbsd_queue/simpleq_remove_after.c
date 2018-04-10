#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void simpleq_remove_after(Node * head, Node * elm)
{
  //pre
  Node * elmn = elm->next;
  Node * elmnn = elmn->next;
  elm->next =elmnn;
  if (elmnn == NULL) {
    head->last = elm;
  }
  free(elmn);
  //post
}

int main(int argc , char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * hd = create_queue(size);
    Node * listelm = hd->next;
    simpleq_remove_after(hd, listelm);
    return 0;
}
