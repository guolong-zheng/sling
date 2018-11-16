#include "stdhipmem.h"



DLNode * g_list_find(DLNode * list, int data) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * curr = list;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (curr->key == data) {
      break;
    }
    curr = curr->next;
  }
  return curr;
}
