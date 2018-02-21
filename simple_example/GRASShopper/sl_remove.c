// ---- Definitions for GRASShopper examples  ----
#include "sl.h"
#include <stdlib.h>

/*D_defs
define pred list^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt) * list^(nxt))
  ) ;

define relation lseg^(head, tail):
  (
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) |
          ((head |-> loc next: nxt) * lseg^(nxt, tail))
  )
axiom: (
      (list^(tail) -* list^(head)) &
      (((tail |-> loc next: virtual tn) * list^(tn)) -* ((lseg^(head, tn) * list^(tn))))
     ) ;
*/
// -----------------------------------------------


Node * sl_remove(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (lst == NULL) {
    return NULL;
  } else {
    int nondet;
    Node * curr = lst;
    while(nondet && curr->next != NULL)
      /*D_invariant (((~ (curr l= nil)) & lseg^(curr, nil)) * lseg^(lst, curr)) */
    {
      nondet = rand();
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

int main(){
    Node * lst = create_list(5);
    Node * res = sl_remove(lst);
    return 0;
}
