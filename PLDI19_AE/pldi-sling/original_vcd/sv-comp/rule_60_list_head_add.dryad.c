// ---- Definitions for sv-comp examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag slave_item */
struct list_head {
  struct list_head * next;
  struct list_head * prev;
};

/*D_defs 
define pred dllnext^(x):
 (
   (((x l= nil) & emp) |

    ((x |-> loc next: y) & (y l= nil))) |

     (
          (((x |-> loc next: nxt) * (nxt |-> secondary prev: x)) * true) &
          (  (x |-> loc next: nxt) * ((~(nxt l= nil)) & dllnext^(nxt)) )
    )
 )
 axiom: sll^(x);

define pred dllprev^(x):
 (
   (((x l= nil) & emp) |

    ((x |-> loc next: y) & (y l= nil))) |

     (
          (((x |-> loc prev: prv) * (prv |-> secondary next: x)) * true) &
          (  (x |-> loc prev: prv) * ((~(prv l= nil)) & dllprev^(prv)) )
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
// -------------------------------------------


_(dryad)
void * list_add(struct list_head * elem, struct list_head * head)
  /*D_requires ((~ (elem l= nil)) 
               * (((head |-> loc next: nxt; loc prev: prv) * true) & (dllnext^(nxt) * dllprev^(prv)))) */

  /*D_ensures ((head |-> loc next: elem; loc prev: prv) * (dllnext^(elem) * dllprev^(prv))) */
{

    struct list_head * next = head->next;
    elem->next = NULL;
    elem->prev = NULL;
    elem->inserted = 1;
    head->next = elem;
    elem->prev = head;
    elem->next = next;
    next->prev = elem;
}
