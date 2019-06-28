#include "stdhipmem.h"

struct llist *create_llist()
/*@
   infer[@shape]
   requires true
   ensures true;
*/
{
  //pre
  struct llist *l = malloc(sizeof(struct llist));
  struct node *n = malloc(sizeof(struct node));
  n->next = NULL;
  n->value = 0;
  l->first = n;
  l->last = n;
  //post
  return l;
}

