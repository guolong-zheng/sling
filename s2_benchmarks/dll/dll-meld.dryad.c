
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

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

