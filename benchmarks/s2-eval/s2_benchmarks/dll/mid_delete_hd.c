#include "stdhipmem.h"



DLNode* dll_mid_delete(DLNode* hd, DLNode* p)
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

  if (hd == p) {
    hd = p->next;
  }

  free(p);
  p = NULL;
  //post
  return hd;
}
