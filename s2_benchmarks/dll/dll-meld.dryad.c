#include "stdhipmem.h"



void dll_meld(DLNode * u, DLNode * v)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if (v != NULL) {
    v->prev = u;
  } 

  if (u != NULL) {
    u->next = v;
  }
 
}

