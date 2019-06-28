#include "stdhipmem.h"



void dl_dispose(DLNode * a, DLNode * b)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * prv = NULL;
  while(a != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    prv = a;
    a = a->next;
    free(prv);
  }
}
