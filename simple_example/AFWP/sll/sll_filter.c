#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * filter(Node * h)
  /*D_requires (sll^(h) & (~ (to_remove(h)))) */
  /*D_ensures  (sll^(h) & (sll^(ret) * true)) */
{
  //pre
  Node * i = h;
  Node * j = NULL;
  Node * inxt = NULL;
  while(i != NULL)
  {
    //loop
    if (rand()%10 > 5) {
      inxt = i->next;
      j->next = inxt;
    } else {
      j = i;
    }
    i = i->next;
  }
  //post
  return j;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * h = create_list(size);
    Node * res = filter(h);
    return 0;
}
