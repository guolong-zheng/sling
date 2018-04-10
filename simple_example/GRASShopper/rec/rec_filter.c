#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * rec_filter(Node * x)
{
  //pre
  Node * n1;
  Node * n2;
  int nondet;
  if (x == NULL) {
    return x;
  } else if (nondet) {
    n1 = x->next;
    n2 = rec_filter(n1);
    x->next = n2;
    //post
    return x;
  } else {
    n1 = x->next;
    free(x);
    n2 = rec_filter(n1);
    //post
    return n2;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res = rec_filter(lst);
    return 0;
}
