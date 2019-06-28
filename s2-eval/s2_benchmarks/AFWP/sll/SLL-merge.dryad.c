#include "stdhipmem.h"



Node * SLL_merge(Node * i, Node * j)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * h = i;
  Node * k = NULL;
  while(i != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (j == NULL || i->key <= j->key) {
      k = i;
      i = i->next;
    } else { 
      k->next = j;
      k = j;
      j = j->next;
      k->next = i;
    }
  }
  return h;
}
