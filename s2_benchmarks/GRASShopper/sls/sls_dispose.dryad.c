
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

void sls_dispose(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  while(lst != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * curr = lst;
    lst = lst->next;
    free(curr);
  }
}
