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


DLNode * dl_remove(DLNode * lst)
  /*D_requires dll^(lst) */
  /*D_ensures  dll^(ret) */
{
  if (lst == NULL) {
    return NULL;
  } else {
    int nondet;
    DLNode * curr = lst;
    while(nondet && curr->next != NULL)
      /*D_invariant ((dll^(lst) & (~ (curr l= nil))) & (lseg^(lst, curr) * dll^(curr))) */
    {
      nondet = rand();
      curr = curr->next;
    }
    DLNode * tmp = curr->next;
    if (tmp != NULL) {
      DLNode * tmp_next = tmp->next;
      curr->next = tmp_next;
      if(tmp_next != NULL){
        tmp_next->prev = curr;
      }
      free(tmp);
    }
    return lst;
  }
}

int main(){
    DLNode * lst = create_list(5);
    DLNode * res = dl_remove(lst);
    return 0;
}
