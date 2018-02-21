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


Node * sl_insert(Node * lst, Node * elt)
  /*D_requires (lseg^(lst, nil) * ((elt |-> loc next: nil))) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (lst == NULL) {
    return elt;
  } else {
    int nondet;
    Node * curr = lst;
    while(nondet && curr->next != NULL)
      /*D_invariant (((~ (curr l= nil)) & lseg^(curr, nil)) * (lseg^(lst, curr))) */
    {
      nondet = rand();
      curr = curr->next;
    }
    Node * curr_next = curr->next;
    elt->next = curr_next;
    curr->next = elt;
    return lst;
  }
}

int main(){
    Node * lst = create_list(5);
    Node * elt = (Node *)malloc(sizeof(Node));
    elt->next = NULL;
    Node * res = sl_insert(lst, elt);

    return 0;
}
