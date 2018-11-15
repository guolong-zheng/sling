
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * dll_append(DLNode * x1, DLNode * x2) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x1 == NULL) {
    return x2;
  } else {
    DLNode * tmp = dll_append(x1->next, x2);
    x1->next = tmp;
    if (tmp) tmp->prev = x1;
    return x1;
  }
}
