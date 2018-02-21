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

DLNode * dl_reverse(DLNode * lst)
  /*D_requires dll^(lst) */
  /*D_ensures dll^(ret) */
{
  DLNode * curr = lst;
  DLNode * rev = NULL;
  while(curr != NULL)
    /*D_invariant (dll^(rev) * dll^(curr)) */
  {
    DLNode * tmp;
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    if(rev != NULL) {
      rev->prev = tmp;
    }
    rev = tmp;
  }
  return rev;
}

int main(){
    DLNode * root = create_list(5);
    DLNode * res = dl_reverse(root);

    return 0;
}
