#include "stdhipmem.h"



DLNode * g_list_reverse(DLNode * list) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * last = NULL;
  DLNode * curr = list;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    last = curr;
    curr = curr->next;
    DLNode * last_prev = last->prev;
    last->next = last_prev;
    last->prev = curr;
  }
  return last;
}
