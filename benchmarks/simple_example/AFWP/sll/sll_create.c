#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * create(int sz)
{
  //pre
  Node * h = NULL;
  Node * e = NULL;
  while(sz > 0)
  {
    //loop
    sz --;
    e = (Node *)malloc(sizeof(Node));
    e->next = h;
    h = e;
  }
  //post
  return h;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * res = create(size);
    return 0;
}
