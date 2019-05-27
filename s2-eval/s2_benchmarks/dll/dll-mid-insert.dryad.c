#include "stdhipmem.h"



DLNode * dll_mid_insert(DLNode * u, DLNode * v, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  DLNode * r = (DLNode *) malloc(sizeof(DLNode)); 

  r->key = k;
  r->prev = u;
  r->next = v;
  if (u != NULL) {
    u->next = r;
  }
  if (v != NULL) {
    v->prev = r;
  }
  return r;
}
