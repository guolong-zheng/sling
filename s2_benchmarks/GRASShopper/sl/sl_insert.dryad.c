
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

_(pure) int havoc();

Node * sl_insert(Node * lst, Node * elt)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst == NULL) {
    return elt;
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
    Node * curr_next = curr->next;
    elt->next = curr_next;
    curr->next = elt;
    return lst;
  }
}
