2// ---- Commmon definitions for doubly-linked list examples  ----
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
 );
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ; */
// -------------------------------------------------------------- 

_(dryad)
DLNode * dll_append(DLNode * x1, DLNode * x2) 
  /*D_requires (dll^(x1) * dll^(x2)) */
  /*D_ensures  (dll^(ret) & (keys^(ret) s= (old(keys^(x1)) union old(keys^(x2))))) */
{
  if (x1 == NULL) {
    return x2;
  } else {
    DLNode * tmp = dll_append(x1->next, x2);
    x1->next = tmp;
    if (tmp) tmp->prev = x1;
    return x1;
  }
}
