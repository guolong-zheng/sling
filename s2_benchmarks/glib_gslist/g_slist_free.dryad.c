
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

void g_slist_free(Node * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  
  Node * x = l;
  while(x != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * next = x->next;
    free(x);
    x = next;
  }
}
