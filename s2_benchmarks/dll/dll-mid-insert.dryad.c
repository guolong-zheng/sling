
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * dll_mid_insert(DLNode * u, DLNode * v, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  DLNode * r = (DLNode *) malloc(sizeof(DLNode)); 
  _(assume r != NULL)
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
