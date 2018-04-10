#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void rec_concat(Node * a, Node * b);
Node * find_last(Node * a);

Node * find_last(Node * a)
{
    if(a->next != NULL) {
      Node * n2 = find_last(a->next);
      return n2;
    } else {
      return a;
    }
}

void rec_concat(Node * a, Node * b)
{
  //pre
  Node * l = find_last(a);
  l->next = b;
  //post
}


int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * a = create_list(size);
    Node * b = create_list(size);
    rec_concat(a, b);
    return 0;
}
