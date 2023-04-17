#include "stdhipmem.h"



int g_list_position(DLNode * list, DLNode * link) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  int i;

  i = 0;
  while(list != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (list == link) {
      return i;
    }
    i ++;
    list = list->next;
  }
  return -1;
}
