#include "stdhipmem.h"



DLNode * dl_filter(DLNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  DLNode * prv = NULL;
  DLNode * curr = x;
  DLNode * res = x;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    DLNode * old_curr = curr;
    curr = curr->next;
    int nondet;
    if(nondet) {
      if (prv != NULL) {
        DLNode * old_curr_next = old_curr->next;
        prv->next = old_curr_next;
        if (old_curr_next != NULL) {
          old_curr_next->prev = prv;
        }
      } else {
        res = old_curr->next;
      }
      free(old_curr);
    } else {
      prv = old_curr;
    }
  }
  return res;
}
