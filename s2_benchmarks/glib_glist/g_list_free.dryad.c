
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

void g_list_free(DLNode * list) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  DLNode * x = list;
  while(x != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    DLNode * next = x->next;
    free(x);
    x = next; 
  }
}
