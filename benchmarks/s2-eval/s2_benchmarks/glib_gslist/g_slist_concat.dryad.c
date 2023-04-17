#include "stdhipmem.h"


Node * g_slist_concat(Node * list1, Node * list2)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (list2 != NULL) {
    if (list1 != NULL) {
      Node * last = g_slist_last(list1);
      last->next = list2;
    } else {
      list1 = list2;
    }
  }
  return list1;
}
