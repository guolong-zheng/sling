
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

void dispose(Node * lst _(out \oset ALL_REACH))
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
