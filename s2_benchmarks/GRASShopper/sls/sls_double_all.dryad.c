
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * sls_double_all(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst == NULL) {
    return NULL;
  } 

  Node * curr = lst;
  Node * cp = NULL;
  Node * res = (Node *) malloc(sizeof(Node));  
  _(assume res != NULL)
  cp = res;
  int curr_key = curr->key;
  cp->key = _(unchecked) (2 * curr_key);
  cp->next = NULL;
  while(curr->next != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    _(assume new_cp != NULL)
    old_cp->next = cp;
    curr = curr->next;
    curr_key = curr->key;
    cp->key = _(unchecked)(2 * curr_key);
    cp->next = NULL;
  }
  return res;
}
