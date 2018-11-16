#include "stdhipmem.h"



Node * SLL_reverse(Node * h)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * i = h;
  Node * j = NULL;
  while(i != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
   {
    Node * k = i->next;
    i->next = j;
    j = i;
    i = k;
  }
  return j;
}
