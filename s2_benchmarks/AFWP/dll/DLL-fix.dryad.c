#include "stdhipmem.h"


DLNode * polarize(DLNode * h) 
/*@
   infer[@shape]
   requires true
   ensures true;
 */
{
  DLNode * i = h;
  DLNode * j = NULL;
  while(i != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
 */
  { 
    DLNode * k = j;
    j = (DLNode *) malloc(sizeof(DLNode));
    j->next = k;
    k->prev = j;
    i = i->next;
  }
  return j;
}
