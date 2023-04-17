#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * swap(Node * h)
{
  //pre
  if (h != NULL) {
    Node * i = h->next;
    if (i != NULL) {
      Node * j = h;
      h = h->next;
      Node * t = h->next;
      j->next = t;
      h->next = j;
    }
  }
  //post
  return h;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * h = create_list(size);
    Node * res = swap(h);
    return 0;
}
