
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * dl_copy(DLNode * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  DLNode * curr = lst;
  DLNode * cp = NULL;
  while(curr != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    DLNode * old_cp = cp;
    cp = (DLNode *) malloc(sizeof(DLNode));
    _(assume cp != NULL)
    cp->next = old_cp;
    if (old_cp != NULL) {
      old_cp->prev  = cp;
    }
    curr = curr->next;
 
  }
  return cp;
}

