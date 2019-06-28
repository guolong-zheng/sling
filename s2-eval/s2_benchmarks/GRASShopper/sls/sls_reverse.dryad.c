#include "stdhipmem.h"



Node * sls_reverse(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr = lst;
  Node * rev = NULL;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * tmp;
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    rev = tmp;
  }
  return rev;
}
