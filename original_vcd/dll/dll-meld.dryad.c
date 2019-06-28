// ---- Commmon definitions for doubly-linked list examples  ----
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
          ( (x |-> loc next: nxt) * ((~(nxt l= nil)) & dll^(nxt)) )
    )
 );

define pred rev-dll^(x):
 (
   (((x l= nil) & emp) |

    ((x |-> loc prev: y) & (y l= nil))) |

     (
          (((x |-> loc prev: prv) * (prv |-> secondary next: x)) * true) &
          ( (x |-> loc prev: prev) * ((~(prev l= nil)) & rev-dll^(prv)) )
    )
 );
   
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define set-fun rev-keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc prev: prv; int key: ky) * true): 
    ((singleton ky) union rev-keys^(prv));
   default: emptyset
  ) ;
*/
// --------------------------------------------------------------


_(dryad)
void dll_meld(DLNode * u, DLNode * v)
  /*D_requires dll^(v) * rev-dll^(u) */
  /*D_ensures (((dll^(v) & (keys^(v) s= old(keys^(v)))) * (rev-dll^(u) & (rev-keys^(u) s= old(rev-keys^(u))))) 
            & (((u l= nil) | ((u |-> loc next: v) * true)) 
            &  ((v l= nil) | ((v |-> loc prev: u) * true)))) */
{

  if (v != NULL) {
    v->prev = u;
  } 

  if (u != NULL) {
    u->next = v;
  }
 
}

