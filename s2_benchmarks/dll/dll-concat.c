#include "stdhipmem.h"
#include <stdio.h>


DLNode* dll_concat(DLNode* a, DLNode* b)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  //pre
  if (a == NULL) {
    //post
    return b;
  } else {
    DLNode* curr = a;
    while (curr->next != NULL)
    /*@
 infer[@shape]
 requires true
 ensures true;
 */
    {
      //loop
      curr = curr->next;
    }

    curr->next = b;
    if (b != NULL) {
      b->prev = curr;
    }

    //post
    return a;
  }
}
