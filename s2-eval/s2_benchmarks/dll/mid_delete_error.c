#include "stdhipmem.h"

void dll_mid_delete(DLNode * p)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  DLNode * v = p->next;
  DLNode * u = p->prev;
  if (v != NULL) {
    v->prev = u;
  }
  if (u != NULL) {
    u->next = v;
  }
  free(p);
  p = NULL;
  //post
}
