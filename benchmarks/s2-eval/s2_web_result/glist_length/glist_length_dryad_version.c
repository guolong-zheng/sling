#include "stdhipmem.h"

int g_list_length(DLNode * list)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  int length;
  length = 0;
  while(list != NULL)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
  {
    length ++;
    list = list->next;
  }
  //post
  return length;
}
