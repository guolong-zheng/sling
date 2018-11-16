#include "stdhipmem.h"



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
  cp = res;
  int curr_key = curr->key;
  cp->key =  (2 * curr_key);
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
    old_cp->next = cp;
    curr = curr->next;
    curr_key = curr->key;
    cp->key = (2 * curr_key);
    cp->next = NULL;
  }
  return res;
}
