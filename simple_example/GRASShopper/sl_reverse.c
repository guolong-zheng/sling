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

Node * sl_reverse(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(ret, nil) */
{
  Node * curr = lst;
  Node * rev = NULL;
  while(curr != NULL)
    /*D_invariant (lseg^(rev, nil) * lseg^(curr, nil)) */
  {
    Node * tmp;
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    rev = tmp;
  }
  return rev;
}

int main(){
    Node * lst = create_list(5);
    Node * res = sl_reverse(lst);
    return 0;
}
