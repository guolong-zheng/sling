#include "stdhipmem.h"



void dispose(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  while(lst != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * curr = lst;
    lst = lst->next;
    free(curr);
  }
}
