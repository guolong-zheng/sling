#include "stdhipmem.h"


void llist_dispose(struct llist *list)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  struct node *n = list->first;
  struct node *l = list->last;
  struct node *next = NULL;
  while (n != l)
  {
    //loop
    next = n->next;
    free(n);
    n = next;
  }
  free(l);
  freel(list);
  //post
}

