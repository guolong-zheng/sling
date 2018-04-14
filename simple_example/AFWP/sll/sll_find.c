#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sll_find(Node * h)
  /*D_requires sll^(h) */
  /*D_ensures  (sll^(h) & (sll^(ret) * true)) */
{
  //pre
  Node * i = h;
  Node * j = NULL;
  Node * t = NULL;
  while(i != NULL && t == NULL)
    /*D_invariant (sll^(i) & ((t l= nil) | (sll^(t) * true))) */
  {
    //loop
    if(rand()%10 > 5) {
      t = i;
    } else {
      i = i->next;
    }
  }
  //post
  return t;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * h = create_list(size);
    Node * res = sll_find(h);
    return 0;
}
