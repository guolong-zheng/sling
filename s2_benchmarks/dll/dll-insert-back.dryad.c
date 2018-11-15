
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * dll_insert_back(DLNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL) {
    DLNode * tail = (DLNode *) malloc(sizeof(DLNode));
    _(assume tail != NULL)
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
