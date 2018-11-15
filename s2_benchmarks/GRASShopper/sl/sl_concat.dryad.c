
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

Node * concat(Node * a, Node * b)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (a == NULL) {
    return b;
  }  else {
    Node * curr;
    curr = a;
    while(curr->next != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
       curr = curr->next;
    }
    curr->next = b;
    return a;
  }
}
