
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

Node * find_last(Node * a)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{ 
    if(a->next != NULL) {
      Node * n2 = find_last(a->next);
      return n2;
    } else {
      return a;
    }
} 

void rec_concat(Node * a, Node * b)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * l = find_last(a);
  l->next = b;
}
