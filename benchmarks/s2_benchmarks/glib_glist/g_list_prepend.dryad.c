#include "stdhipmem.h"


DLNode * g_list_prepend(DLNode * list, int data, DLNode * p) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  DLNode * ret = (DLNode *) malloc(sizeof(DLNode));
  ret->key = data;
  ret->next = list;
  ret->prev = p;
  if (list != NULL) {
    list->prev = ret;
  }
  if (p != NULL) {
     p->next = ret;
  }
  return ret;
}
