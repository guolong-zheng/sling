
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * g_list_find(DLNode * list, int data) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr = list;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (curr->key == data) {
      break;
    }
    curr = curr->next;
  }
  return curr;
}
