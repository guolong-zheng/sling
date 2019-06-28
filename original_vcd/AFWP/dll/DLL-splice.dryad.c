// ---- Definitions for AFWP examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
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
   

define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt) * sll^(nxt))  
  )
  axiom: lseg^(x, x) ;

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
// ----------------------------------------

_(dryad)
void splice(DLNode * h, DLNode * i)
  /*D_requires (lseg^(h, i) * ((~(i l= nil)) & dll^(i))) */
  /*D_ensures (dll^(h) * dll^(i)) */
{ 
  DLNode * j;
  if (h != NULL && i != h) 
  {
    j = i->prev;
    i->prev = NULL;
    j->next = NULL;
  }
}
