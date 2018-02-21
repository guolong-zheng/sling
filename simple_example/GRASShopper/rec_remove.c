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

Node * rec_remove(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(ret, nil) */
{
  int nondet;
  if (lst == NULL) {
    return NULL;
  } else if (nondet) {
    Node * n = lst->next;
    free(lst);
    return n;
  } else {
    Node * n1 = lst->next;
    Node * n2 = rec_remove(n1);
    lst->next = n2;
    return lst;
  }
}

int main(){
    Node * lst = create_list(5);
    Node * res = rec_remove(lst);
    return 0;
}
