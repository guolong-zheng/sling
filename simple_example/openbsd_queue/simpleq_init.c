#include "openbsd_queue.h"
#include <stdlib.h>

/*D_defs
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define int-fun length^(x):
  (case (x l= nil): 0;
   case ((x |-> loc next: nxt; int key: ky) * true):
    (1 + length^(nxt));
   default: 0
  ) ;

define pred sll^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt) * sll^(nxt))
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (length^(x) i= 0)) | ((~ (x l= nil)) & (0 < length^(x)))));

define relation lseg^(head, tail):
  (
  ((head l= tail) & emp) |
          ((head |-> loc next: nxt) * lseg^(nxt, tail))
  )
  axiom: ( (((head l= tail) => (emp & ((lseg-length^(head, tail) i= 0) & (lseg-keys^(head, tail) s= emptyset)))) & ((tail l= nil) => (sll^(head) & ((length^(head) i= lseg-length^(head, tail)) & (keys^(head) s= lseg-keys^(head, tail)))))) &
  ( (sll^(tail) -* (sll^(head) & ( (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))) & (length^(head) i= (lseg-length^(head, tail) + length^(tail))) ))) &
    (((tail |-> loc next: virtual tn) * sll^(tn)) -* ((lseg^(head, tn) & ( (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk))) & (lseg-length^(head, tn) i= (lseg-length^(head, tail) + 1)) )) * sll^(tn))) ) ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case (head l= tail) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;

define bin-int-fun lseg-length^(head, tail):
  (case (head l= tail) : 0;
   case ((head |-> loc next: nxt; int key: ky) * true):
    (1 + lseg-length^(nxt, tail));
   default: 0
  ) ;
*/
// --------------------------------------------------------

void simpleq_init()
  /*D_requires emp */
  /*D_ensures (((nill l= nil) & (head |-> loc next: fst; loc last: lst)) * ((((fst l= nil) & (lst l= head)) & emp) | (lseg^(fst, lst) * (lst |-> loc next: nill)))) */
{
  Node * head = (Node *) malloc(sizeof(Node));
  head->next = NULL;
  head->last = head;
}

int main(){
    simpleq_init();
    return 0;
}
