
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * swap(Node * h) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (h != NULL) {
    Node * i = h->next;
    if (i != NULL) {  
      Node * j = h;
      h = h->next;
      Node * t = h->next;
      j->next = t;
      h->next = j;
    }
  }
  return h;
}
