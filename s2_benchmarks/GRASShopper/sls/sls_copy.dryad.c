
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * sls_copy(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * head = NULL;
  if (lst == NULL) {
    return NULL;
  } 
  
  Node * curr = lst;
  head = (Node *) malloc(sizeof(Node));  
  _(assume head != NULL)
  Node * cp = head;
  int lst_key = lst->key;
  cp->key = lst_key; 
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
    _(assume cp != NULL)

    old_cp->next = cp;
    curr = curr->next;
    int curr_key = curr->key;
    cp->key = curr_key;
    cp->next = NULL;

  }
  return head;
}
