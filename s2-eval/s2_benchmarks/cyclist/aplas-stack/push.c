#include "stdhipmem.h"

void push(struct stack* s, int x)
  /*@
    infer[@shape]
    requires true
    ensures true;
  */
{
  //pre
  struct node* n = malloc(sizeof(struct node));
  n->next = s->head;
  n->value = x;
  s->head = n;
  //post
}

