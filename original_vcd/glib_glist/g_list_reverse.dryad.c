// ---- Definitions for glib/glist examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

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
// ------------------------------------------------

_(dryad)
DLNode * g_list_reverse(DLNode * list) 
  /*D_requires (dll^(list) 
               & ((list l= nil) 
                 | ((list |-> loc prev: nill) * (nill l= nil)))) */
  /*D_ensures ((dll^(ret) & (keys^(ret) s= old(keys^(list)))) 
              & ((ret l= nil) | ((ret |-> loc prev: curr) * true))) */
{
  DLNode * last = NULL;
  DLNode * curr = list;
  while(curr != NULL) 
    /*D_invariant (((dll^(curr) * dll^(last)) & ((keys^(curr) union keys^(last)) s= old(keys^(list)))) 
                  & ((((last l= nil) | (last |-> loc prev: curr)) 
                     * ((curr l= nil) | (curr |-> loc prev: last))) 
                    * true)) */
  {
    last = curr;
    curr = curr->next;
    DLNode * last_prev = last->prev;
    last->next = last_prev;
    last->prev = curr;
  }
  return last;
}
