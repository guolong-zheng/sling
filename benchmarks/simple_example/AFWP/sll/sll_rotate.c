#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void rotate(Node * h, Node * j)
  /*D_requires (lseg^(h, j) * sll^(j)) */
  /*D_ensures  sll^(h) */
{
  //pre
  if (h != NULL && h != j) {
    Node * k = h->next;
    h->next = NULL;
    j->next = h;
    j = h;
    h = k;
  }
  //post
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * h = create_list(size);
    Node * j = h->next->next;
    rotate(h, j);
    return 0;
}
