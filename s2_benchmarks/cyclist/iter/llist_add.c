#include "stdhipmem.h"


struct llist * llist_add(struct llist *list, int x)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  struct node *l = NULL;
  struct node *n = malloc(sizeof(struct node));
  n->next = NULL;
  n->value = 0;
  l = list->last;
  l->next = n;
  l->value = x;
  list->last = n;
  //post
  return list;
}

