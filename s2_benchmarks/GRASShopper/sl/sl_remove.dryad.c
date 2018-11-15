
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

_(pure) int havoc();
  
_(dryad)
Node * sl_remove(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst == NULL) {
    return NULL;
  } else {
    int nondet;
    Node * curr = lst;
    while(nondet && curr->next != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      nondet = havoc();
      curr = curr->next;
    }
    Node * tmp = curr->next;
    if (tmp != NULL) {
      Node * tmp_next = tmp->next;
      curr->next = tmp_next;
      free(tmp);
    }
    return lst;
  }
}
