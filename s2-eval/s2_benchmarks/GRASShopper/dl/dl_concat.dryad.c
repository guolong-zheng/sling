#include "stdhipmem.h"



DLNode * dl_concat(DLNode * a, DLNode * b)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (a == NULL) {
    return b;
  }  else {
    DLNode * curr;
    curr = a;
    while(curr->next != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
       curr = curr->next;
    }
    curr->next = b;
    if (b != NULL) {
      b->prev = curr;
    }
    return a;
  }
}
