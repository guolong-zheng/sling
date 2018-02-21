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


Node * rec_copy_loop(Node * curr, Node * cp)
  /*D_requires (lseg^(cp, nil)  * lseg^(curr, nil)) */
  /*D_ensures  (lseg^(ret, nil) * lseg^(curr, nil)) */
{
  if (curr == NULL) {
    return cp;
  } else {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    cp->next = old_cp;
    Node * curr_next = curr->next;
    Node * res = rec_copy_loop(curr_next, cp);
    return res;
  }
}

Node * rec_copy(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  (lseg^(lst, nil) * lseg^(ret, nil)) */
{
  return rec_copy_loop(lst, NULL);
}

int main(){
    Node * lst = create_list(5);
    NOde * res = rec_copy(lst);

    return 0;
}
