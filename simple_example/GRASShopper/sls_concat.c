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

Node * sls_concat(Node * a, Node * b)
  /*D_requires (sorted-sll^(b) & ((b l= nil) | (((b |-> int key: ky) * true) * (sorted-sll^(a) & (keys^(a) set-le ky))))) */
  /*D_ensures sorted-sll^(ret) */
{

  if (a == NULL) {
    return b;
  }  else {
    Node * curr;
    curr = a;
    while(curr->next != NULL)
      /*D_invariant (sorted-lseg^(a, curr) * ((~ (curr l= nil)) & sorted-sll^(curr))) */
    {
       curr = curr->next;
    }
    curr->next = b;
    return a;
  }
}

int main(){
    Node * a = create_list(1, 5);
    Node * b = create_list(10, 5);
    Node * res = sls_concat(a,b);
    return 0;
}
