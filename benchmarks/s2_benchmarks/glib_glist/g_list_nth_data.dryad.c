#include "stdhipmem.h"



int g_list_nth_data(DLNode * list, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  int res;
  while(n > 0 && list != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    n --;
    list = list->next;
  }
  if (list != NULL) {
    res = list->key;
  } else {
    res = 0;
  }
  return res;
}             

