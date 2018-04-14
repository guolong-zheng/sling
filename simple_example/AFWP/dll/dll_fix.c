#include <stdio.h>
#include <stdlib.h>
#include "header.h"

DLNode * polarize(Node * h)
  /*D_requires sll^(h)   */
  /*D_ensures  dll^(ret) */
{
  Node * i = h;
  DLNode * j = NULL;
  DLNode * k = NULL;
  //pre
  while(i != NULL)
      /*D_invariant (sll^(i) * dll^(j)) */
  {
    //loop
    k = j;
    j = (DLNode *) malloc(sizeof(DLNode));
    j->next = k;
    if(k!= NULL)
        k->prev = j;
    i = i->next;
  }
  //post
  return j;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * root = create_sll(size);
    DLNode * res = polarize(root);
    return 0;
}
