#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sll_reverse(Node * h)
  /*D_requires sll^(h)   */
  /*D_ensures  sll^(ret) */
{
  //pre
  Node * i = h;
  Node * j = NULL;
  Node * k = NULL;
  while(i != NULL)
    /*D_invariant (sll^(i) * sll^(j)) */
   {
    //loop
    k = i->next;
    i->next = j;
    j = i;
    i = k;
  }
  //post
  return j;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * h = create_list(size);
    Node * res = sll_reverse(h);
    sll_reverse(NULL);
    return 0;
}
