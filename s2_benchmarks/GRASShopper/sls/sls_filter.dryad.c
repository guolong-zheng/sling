
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * sls_filter(Node * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * prv = NULL;
  Node * curr = x;
  Node * res = x;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * old_curr = curr;
    curr = curr->next;
    int nondet;
    if(nondet) {
      if (prv != NULL) {
        Node * old_curr_next = old_curr->next;
        prv->next = old_curr_next;
      } else {
        res = old_curr->next;
      }
      free(old_curr);
    } else {
      prv = old_curr;
    }
  }
  return res;
}
