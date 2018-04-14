#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sll_last(Node * h)
  /*D_requires sll^(h) */
  /*D_ensures  (lseg^(h, ret) * sll^(ret)) */
{
  //pre
  Node * i = h;
  Node * j = NULL;
  while(i != NULL)
    /*D_invariant (lseg^(h, j) & (((j l= nil) | (((j |-> loc next: i) * true))) * sll^(i))) */
  {
    //loop
    j = i;
    i = i->next;
  }
  //post
  return j;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * h = create_list(size);
    Node * res = sll_last(h);
    return 0;
}
