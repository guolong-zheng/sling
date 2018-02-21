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


void rec_traverse(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(lst, nil) */
{
  if (lst != NULL) {
    Node * n = lst->next;
    rec_traverse(n);
  }
}

int main(){
    Node * lst = create_list(5);
    rec_traverse(lst);
    return 0;
}
