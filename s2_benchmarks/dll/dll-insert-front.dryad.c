
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * dll_insert_front(DLNode * x, int k) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL) {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    _(assume head != NULL)
    head->key = k;
    head->next = NULL;
    head->prev = NULL;
    return head;
  } else {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    _(assume head != NULL)
    head->key = k;
    head->next = x;
    x->prev = head;
    return head;
  }
}


