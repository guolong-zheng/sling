#include "stdhipmem.h"



void rec_traverse(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst != NULL) {
    Node * n = lst->next;
    rec_traverse(n);
  }
}
