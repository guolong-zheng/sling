#include "stdhipmem.h"

int llist_lookup(struct llist *list, int index)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{

  struct node *f = list->first;
  struct node *l = list->last;
  struct node *n = f;
  struct node *next = NULL;
  int i = 0;
  while (i < index)
  {

    next = n->next;
    n = next;
    i = i + 1;
  }
  int value = n->value;

  return value;
}

