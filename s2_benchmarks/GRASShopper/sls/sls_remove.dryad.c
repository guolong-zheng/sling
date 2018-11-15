
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * sls_remove(Node * lst, int value)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * curr = lst;
  Node * prv = NULL;
  while(curr != NULL && curr->key < value)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    prv = curr;
    curr = curr->next;
  }
    
  if (curr != NULL && curr->key == value)
  {
    if (prv == NULL) {
      lst = curr->next;
    }  else {
      Node * curr_next = curr->next;
      prv->next = curr_next;
    }
    free(curr);
  }
  return lst; 
}
