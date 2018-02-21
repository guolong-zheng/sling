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

DLNode * dl_filter(DLNode * x)
  /*D_requires dll^(x) */
  /*D_ensures  dll^(ret) */
{

  DLNode * prv = NULL;
  DLNode * curr = x;
  DLNode * res = x;
  while(curr != NULL)
    /*D_invariant (dll^(res) & (lseg^(res, prv)
                    * (dll^(prv) & (((prv |-> loc next: curr) * true) | ((prv l= nil))))))  */
  {
    DLNode * old_curr = curr;
    curr = curr->next;
    int nondet;
    if(nondet) {
      if (prv != NULL) {
        DLNode * old_curr_next = old_curr->next;
        prv->next = old_curr_next;
        if (old_curr_next != NULL) {
          old_curr_next->prev = prv;
        }
      } else {
        res = old_curr->next;
      }
      free(old_curr);
    } else {
      prv = old_curr;
    }
  }
  return res;
}

int main(){
    DLNode * root = create_list(5);
    DLNode * res = dl_filter(root);
    return 0;
}
