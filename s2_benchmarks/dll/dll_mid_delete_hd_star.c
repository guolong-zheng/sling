
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
    int key;
    struct node * next;
    struct node * prev;
} DLNode;

void dll_mid_delete(DLNode** hd, DLNode* p)
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

  if (*hd == p) {
    *hd = p->next;
  }

  free(p);
  //post
}

