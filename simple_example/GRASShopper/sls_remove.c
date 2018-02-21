// ---- Definitions for GRASShopper examples  ----
#include "sls.h"
#include <stdlib.h>

/*D_defs
define pred sll^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) * sll^(nxt))
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (keys^(x) s= emptyset)) | ((~ (x l= nil)) & (~ (keys^(x) s= emptyset)))));

define pred sorted-sll^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) *
      (sorted-sll^(nxt) & (ky le-set keys^(nxt)))
      )
  )
  axiom: (sorted-lseg^(x, x) * sll^(x));

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define relation lseg^(head, tail):
  (
  ((head l= tail) & emp) |
          ((head |-> loc next: nxt; int key: ky) * (lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))
  )
  axiom: ( (((head l= tail) => (emp & (lseg-keys^(head, tail) s= emptyset))) & ((tail l= nil) => (sll^(head) & (keys^(head) s= lseg-keys^(head, tail))))) &
  ( (sll^(tail) -* (sll^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * sll^(tn))) ) ) ;

define relation sorted-lseg^(head, tail):
  (
  ((head l= tail) & emp) |
          ((head |-> loc next: nxt; int key: ky) * (sorted-lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))
  )
  axiom: ( lseg^(head, tail) &
    ( ((tail l= nil) => sorted-sll^(head)) &
  ( (sorted-sll^(tail) -* ((lseg-keys^(head, tail) le keys^(tail)) => sorted-sll^(head))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* (((lseg-keys^(head, tail) set-le tk) * true) => (sorted-lseg^(head, tn) * sll^(tn)))) ) ) ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case (head l= tail) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;
*/
// -----------------------------------------------

Node * sls_remove(Node * lst, int value)
  /*D_requires sorted-sll^(lst) */
  /*D_ensures  sorted-sll^(ret) */
{
  Node * curr = lst;
  Node * prv = NULL;
  while(curr != NULL && curr->key < value)
    /*D_invariant (((prv l= nil) * (cur l= lst) & sll^(curr))
                  | (((prv |-> loc next: curr; int key: pky)
                     * (sorted-lseg^(lst, prv) & (lseg-key^(lst, prv) set-le pky)))
                    * (sll^(curr) & ((curr l= nil) | (((curr |-> int key: cky) * true) & pky <= cky)))))
                   */

  {
    prv = curr;
    curr = curr->next;
  }

  if (curr != NULL && curr->key == value)
  {
    if (prv == NULL) {
      lst = curr->next;
    }  else {
      Node * curr_next = curr->next;
      prv->next = curr_next;
    }
    free(curr);
  }
  return lst;
}

int main(){
    Node * lst =create_list(1, 5);
    Node * res = sls_remove(lst, 5);
    return 0;
}
