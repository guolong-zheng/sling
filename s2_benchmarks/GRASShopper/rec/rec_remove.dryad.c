#include "stdhipmem.h"



Node * rec_remove(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  int nondet;
  if (lst == NULL) {
    return NULL;
  } else if (nondet) {
    Node * n = lst->next;
    free(lst);
    return n;
  } else {
    Node * n1 = lst->next;
    Node * n2 = rec_remove(n1);
    lst->next = n2;
    return lst;
  }
}
