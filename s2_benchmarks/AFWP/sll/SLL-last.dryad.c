#include "stdhipmem.h"



Node * SLL_last(Node * h)
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
    j = i;
    i = i->next;
  }
  return j;
}
