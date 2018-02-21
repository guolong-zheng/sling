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

void dispose(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  emp */
{

  while(lst != NULL)
    /*D_invariant lseg^(lst, nil) */
  {
    Node * curr = lst;
    lst = lst->next;
    free(curr);
  }
}

int main(){
    Node * lst = create_list(5);
    dispose(lst);
    return 0;
}
