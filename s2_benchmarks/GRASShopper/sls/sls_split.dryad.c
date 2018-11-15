
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * split(Node * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * z = x;

  Node * curr = x;
  while(curr != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    z = z->next;
    curr = curr->next;
    if (curr != NULL) {
      curr = curr->next;
    }
  }
  if (z != NULL) {
    Node * tmp = z;
    z = z->next;
    tmp->next = NULL;
  } 

  return z;
}

