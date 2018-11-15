
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

void sls_traverse1(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr = lst;
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

void sls_traverse2(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr;
  if (lst != NULL) {
    curr = lst;
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
}
