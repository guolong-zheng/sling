
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * prev;
} DLNode;

void dl_traverse(DLNode * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * curr = lst;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    curr = curr->next;
  }
}

