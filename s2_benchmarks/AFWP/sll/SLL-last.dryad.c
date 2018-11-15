
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * SLL_last(Node * h)
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
    j = i;
    i = i->next;
  }
  return j;
}
