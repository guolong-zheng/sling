
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * g_list_last(DLNode * list) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * curr = list;
  if (curr != NULL) {
    while(curr->next != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      curr = curr->next;
    }
  }
  return curr;
}

