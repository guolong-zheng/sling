#include "stdhipmem.h"



void sl_traverse1(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr = lst;
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

void sl_traverse2(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr;
  if (lst != NULL) {
    curr = lst;
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
}
