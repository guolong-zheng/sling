#include "header.h"
#include <stdlib.h>

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
