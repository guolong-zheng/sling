#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * merge(Node * a, Node * b)
{
  //pre
  Node * res = NULL;
  if (a == NULL) {
    //post
    return b;
  } else if (b == NULL) {
    //post
    return a;
  } else if (a->key <= b->key) {
    res = a;
    a = a->next;
  } else {
    res = b;
    b = b->next;
  }

  Node * last;
  last = res;

  while(a != NULL || b != NULL)
  {
    //loop
    if (a == NULL || (b != NULL && a->key > b->key)) {
      last->next = b;
      last = b;
      b = b->next;
    } else {
      last->next = a;
      last = a;
      a = a->next;
    }
  }
  //post
  return res;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * a = create_list(1, size);
    Node * b = create_list(100, size);
    Node * res = merge(a, b);
    return 0;
}
