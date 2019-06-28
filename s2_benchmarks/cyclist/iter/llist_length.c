#include "stdhipmem.h"

int llist_length(struct llist *list)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{

  struct node *f = list->first;
  struct node *n = f;
  struct node *l = list->last;
  struct node *next = NULL;
  int c = 0;
  while (n != l)
  {

    next = n->next;
    n = next;
    c = c + 1;
  }

  return c;
}

