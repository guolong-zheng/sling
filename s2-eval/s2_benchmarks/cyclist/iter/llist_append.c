#include "stdhipmem.h"

void llist_append(struct llist *list1, struct llist *list2)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{

  struct node *l1 = list1->last;
  struct node *f2 = list2->first;
  struct node *l2 = list2->last;
  if (f2 == l2) {
    free(l2);
    freel(list2);
  } else {
    l1->next = f2->next;
    l1->value = f2->value;
    list1->last = l2;
    free(f2);
    freel(list2);
  }

}
