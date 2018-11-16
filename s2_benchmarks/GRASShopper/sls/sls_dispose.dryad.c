#include "stdhipmem.h"



void sls_dispose(Node * lst)
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
