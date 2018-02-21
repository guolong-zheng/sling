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


Node * concat(Node * a, Node * b)
  /*D_requires (lseg^(a, nil) * lseg^(b, nil)) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (a == NULL) {
    return b;
  }  else {
    Node * curr;
    curr = a;
    while(curr->next != NULL)
      /*D_invariant (((~ (curr l= nil)) & lseg^(curr, nil)) * lseg^(a, curr)) */
    {
       curr = curr->next;
    }
    curr->next = b;
    return a;
  }
}

int main(){
    Node * a = create_list(5);
    Node * b = create_list(5);
    Node * res = concat(a, b);
    return 0;
}
