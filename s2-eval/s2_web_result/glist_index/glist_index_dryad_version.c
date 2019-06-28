#include "stdhipmem.h"



int g_list_index(DLNode * list, int data) 
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
    if (list->key == data) {
      return i;
    }
    i ++;
    list = list->next;
   }
  return -1;
}
