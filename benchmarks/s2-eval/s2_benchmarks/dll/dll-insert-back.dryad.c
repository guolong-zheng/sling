#include "stdhipmem.h"



DLNode * dll_insert_back(DLNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL) {
    DLNode * tail = (DLNode *) malloc(sizeof(DLNode));

    tail->key = k;
    tail->next = NULL;
    tail->prev= x;
    return tail;
  } else {
    DLNode * tmp = dll_insert_back(x->next, k);
    x->next = tmp;
    tmp->prev = x;
    return x;
  }
}
