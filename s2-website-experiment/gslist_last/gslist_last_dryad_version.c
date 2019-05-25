#include "stdhipmem.h"



Node * g_slist_last(Node * list)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if (list != NULL) 
  {
    while(list->next != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      list = list->next;
    }
   
  }
  return list;
}
