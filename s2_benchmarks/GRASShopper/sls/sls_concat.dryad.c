
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * sls_concat(Node * a, Node * b)
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
