// ---- Definitions for GRASShopper examples  ----
#include "dl.h"
#include <stdlib.h>

/*D_defs
define pred dll^(x):
 (
   (((x l= nil) & emp) |

    ((x |-> loc next: y) & (y l= nil))) |

     (
          (((x |-> loc next: nxt) * (nxt |-> secondary prev: x)) * true) &
          (  (x |-> loc next: nxt) * ((~(nxt l= nil)) & dll^(nxt)) )
    )
 )
 axiom: sll^(x);


define pred sll^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt) * sll^(nxt))
  )
  axiom: lseg^(x, x) ;

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

void dl_traverse(DLNode * lst)
  /*D_requires dll^(lst) */
  /*D_ensures  dll^(lst) */
{
  DLNode * curr = lst;
  while(curr != NULL)
    /*D_invariant (lseg^(lst, curr) * dll^(curr)) */
  {
    curr = curr->next;
  }
}

int main(){
    DLNode * lst = create_list(5);
    dl_traverse(lst);
    return 0;
}
