#include "stdhipmem.h"



Node * sls_insert(Node * lst, Node * elt)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst == NULL || lst->key > elt->key) {
    elt->next = lst;
    return elt;
  } else {
    Node * curr = lst;
    while(curr->next != NULL && curr->next->key <= elt->key)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      curr = curr->next;
    }
    Node * curr_next = curr->next;
    elt->next = curr_next;
    curr->next = elt;
    return lst;
  }
}
