#include "stdhipmem.h"

int pop(struct stack* s)
  /*@
   infer[@shape]
   requires true
   ensures true;
  */
{
  //pre
  struct node* tmp = s->head;
  int res = tmp->value;
  s->head = tmp->next;
  free(tmp);
  //post
  return res;
}

