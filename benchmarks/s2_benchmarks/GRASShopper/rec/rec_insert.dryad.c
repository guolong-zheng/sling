#include "stdhipmem.h"



Node * rec_insert(Node * lst, Node * elt)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst == NULL) {
    return elt; 
  } else {
    int nondet;
    if (nondet) {
      elt->next = lst;
      return elt;
    } else {
      Node * n1 = lst->next;
      Node * n2 = rec_insert(n1, elt);
      lst->next = n2;
      return lst;
    }
  }
}
