
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * prev;
} DLNode;

_(pure) int havoc();

DLNode * dl_insert(DLNode * lst, DLNode * elt)
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
    DLNode * curr = lst;
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
    DLNode * curr_next = curr->next;
    elt->next = curr_next;
    if (curr_next != NULL) {
      curr_next->prev = NULL;
    }
    curr->next = elt;
    elt->prev = curr;
    return lst;
  }
}
