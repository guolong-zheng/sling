#include "stdhipmem.h"



DLNode * dll_insert_front(DLNode * x, int k) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL) {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));

    head->key = k;
    head->next = NULL;
    head->prev = NULL;
    return head;
  } else {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));

    head->key = k;
    head->next = x;
    x->prev = head;
    return head;
  }
}


