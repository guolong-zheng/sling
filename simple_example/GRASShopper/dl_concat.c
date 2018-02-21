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

DLNode * dl_concat(DLNode * a, DLNode * b)
  /*D_requires (dll^(a) * dll^(b)) */
  /*D_ensures  (dll^(ret) * lseg^(ret, b)) */
{
  if (a == NULL) {
    return b;
  }  else {
    DLNode * curr;
    curr = a;
    while(curr->next != NULL)
      /*D_invariant (((~ (curr l= nil)) & dll^(a)) & (lseg^(a, curr) * dll^(curr))) */
    {
       curr = curr->next;
    }
    curr->next = b;
    if (b != NULL) {
      b->prev = curr;
    }
    return a;
  }
}

int main(){
    DLNode * a = create_list(5);
    DLNode * b = create_list(5);

    DLNode * res = dl_concat(a, b);

    return 0;
}
