// ---- Definitions for GRASShopper examples  ----
#include "rec.h"
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

Node * rec_filter(Node * x)
  /*D_requires lseg^(x, nil)   */
  /*D_ensures  lseg^(ret, nil) */
{

  Node * n1;
  Node * n2;
  int nondet;
  if (x == NULL) {
    return x;
  } else if (nondet) {
    n1 = x->next;
    n2 = rec_filter(n1);
    x->next = n2;
    return x;
  } else {
    n1 = x->next;
    free(x);
    n2 = rec_filter(n1);
    return n2;
  }
}

int main(){
    Node * x = create_list(5);
    Node * res = rec_filter(x);
    return 0;
}
