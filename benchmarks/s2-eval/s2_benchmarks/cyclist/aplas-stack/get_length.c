#include "stdhipmem.h"

int get_length(struct stack* s)
  /*
    infer[@shape]
    requires true
    ensures true;
  */
{
  int r = 0;
  struct node* n = s->head;
  while(n != NULL)
  /*@
    infer[@shape]
    requires true
    ensures true;
  */
  {
    r = r + 1;
    n = n->next;
  }
  return r;
}
