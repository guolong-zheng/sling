#include "stdhipmem.h"



void g_slist_free(Node * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  
  Node * x = l;
  while(x != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * next = x->next;
    free(x);
    x = next;
  }
}
