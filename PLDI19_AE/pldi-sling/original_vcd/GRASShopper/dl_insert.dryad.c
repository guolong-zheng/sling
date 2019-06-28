// ---- Definitions for GRASShopper examples  ----
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
// -----------------------------------------------

_(pure) int havoc();

_(dryad)
DLNode * dl_insert(DLNode * lst, DLNode * elt)
  /*D_requires (dll^(lst) * ((elt |-> loc next: nil; loc prev: nil))) */
  /*D_ensures  dll^(ret) */
{
  if (lst == NULL) {
    return elt;
  } else {
    int nondet;
    DLNode * curr = lst;
    while(nondet && curr->next != NULL)
      /*D_invariant ((dll^(lst) * (~ (curr l= nil))) & (lseg^(lst, curr) * dll^(curr))) */
    {
      nondet = havoc();
      curr = curr->next;
    }
    DLNode * curr_next = curr->next;
    elt->next = curr_next;
    if (curr_next != NULL) {
      curr_next->prev = NULL;
    }
    curr->next = elt;
    elt->prev = curr;
    return lst;
  }
}
