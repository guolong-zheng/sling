#include "header.h"
#include <stdlib.h>

int rand_num(){
    return rand()%MAX_RAND;
}

Node * create_list(int sz)
{
  Node * h = NULL;
  while(sz > 0)
  {
    sz --;
    Node * e = (Node *)malloc(sizeof(Node));
    e->next = h;
    h = e;
  }
  return h;
}

KNode * create_klist(int sz){
    KNode * h = NULL;
    while(sz > 0)
    {
      sz --;
      KNode * e = (KNode *)malloc(sizeof(KNode));
      e->next = h;
      e->key = rand_num();
      h = e;
    }
    return h;
}
