#include "stdhipmem.h"


void splice(DLNode * h, DLNode * i)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{ 
  DLNode * j;
  if (h != NULL && i != h) 
  {
    j = i->prev;
    i->prev = NULL;
    j->next = NULL;
  }
}
