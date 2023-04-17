#include "stdhipmem.h"



Node * sl_copy(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  Node * curr = lst;
  Node * cp = NULL;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    cp->next = old_cp;
    curr = curr->next;
  }
  return cp;
}
