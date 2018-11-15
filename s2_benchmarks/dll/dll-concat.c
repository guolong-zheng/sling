#include <stdio.h>

typedef
/*D_tag node */
struct node {
    int key;
    struct node * next;
    struct node * prev;
} DLNode;

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
