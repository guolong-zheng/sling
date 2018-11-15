
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

void rotate(Node * h, Node * j)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (h != NULL && h != j) {
    Node * k = h->next;
    h->next = NULL;
    j->next = h;
    j = h;
    h = k;
  }
}
