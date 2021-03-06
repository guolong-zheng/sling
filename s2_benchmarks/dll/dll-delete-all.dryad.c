#include "stdhipmem.h"



DLNode * dll_delete(DLNode * x, int k) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL) {
    return x;
  } else if (x->key == k) {
    DLNode * tmp = dll_delete(x->next, k);
    free(x);
    return tmp;
  } else {
    DLNode * tmp = dll_delete(x->next, k);
    x->next = tmp;
    if (tmp) tmp->prev = x;
    return x;
  }
}
