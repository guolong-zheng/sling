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

Node * sl_filter(Node * x)
  /*D_requires lseg^(x, nil) */
  /*D_ensures  lseg^(ret, nil) */
{
  Node * prv = NULL;
  Node * curr = x;
  Node * res = x;
  while(curr != NULL)
    /*D_invariant ((lseg^(res, prv) * (((prv |-> loc next: curr) * true) | (prv l= nil)))
                  & ((res l= curr) & lseg^(curr, nil))) */
   {
    Node * old_curr = curr;
    curr = curr->next;
     int nondet;
    if(nondet) {
      if (prv != NULL) {
        Node * old_curr_next = old_curr->next;
        prv->next = old_curr_next;
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
    Node * lst = create_list(5);
    Node * res = sl_filter(lst);
    return 0;
}
