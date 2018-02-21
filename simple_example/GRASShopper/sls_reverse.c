// ---- Definitions for GRASShopper examples  ----
#include "sls.h"
#include <stdlib.h>

/* D_defs
define pred sorted^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) *
      (sorted^(nxt) & (ky lt-set keys^(nxt)))
      )
  ) ;

define pred rev_sorted^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) *
      (sorted^(nxt) & (keys^(nxt) set-lt ky))
      )
  ) ;

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;
*/
// -----------------------------------------------

Node * sls_reverse(Node * lst)
  /*D_requires sorted^(lst) */
  /*D_ensures  rev_sorted^(ret) */
{
  Node * curr = lst;
  Node * rev = NULL;
  while(curr != NULL)
    /*D_invariant (rev_sorted^(rev) * sorted^(curr)) */
  {
    Node * tmp;
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    rev = tmp;
  }
  return rev;
}

int main(){
    Node * lst = create_list(1, 5);
    Node * res = sls_reverse(lst);
    return 0;
}
