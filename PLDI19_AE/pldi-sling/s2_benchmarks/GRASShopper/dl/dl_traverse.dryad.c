#include "stdhipmem.h"



void dl_traverse(DLNode * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * curr = lst;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    curr = curr->next;
  }
}

