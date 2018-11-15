
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * SLL_reverse(Node * h)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * i = h;
  Node * j = NULL;
  while(i != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
   {
    Node * k = i->next;
    i->next = j;
    j = i;
    i = k;
  }
  return j;
}
