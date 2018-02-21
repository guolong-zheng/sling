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


void sl_traverse1(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(lst, nil) */
{
  Node * curr = lst;
  while(curr != NULL)
    /*D_invariant (lseg^(lst, curr) * lseg^(curr, nil)) */
  {
    curr = curr->next;
  }
}


void sl_traverse2(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(lst, nil) */
{
  Node * curr;
  if (lst != NULL) {
    curr = lst;
    while(curr != NULL)
    /*D_invariant (lseg^(lst, curr) * lseg^(curr, nil)) */
    {
      curr = curr->next;
    }
  }
}

int main(){
    Node * lst = create_list(5);
    Node * res = sl_traverse1(lst);
    return 0;
}
