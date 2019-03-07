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
          (  (x |-> loc next: nxt) * ((~(nxt l= nil)) & dll^(nxt)) )
    )
 );
   
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;
*/

// --------------------------------------------------------------  

_(dryad)
DLNode * dll_delete(DLNode * x, int k) 
  /*D_requires dll^(x) */
  /*D_ensures  (dll^(ret) 
                & (((k i-in old(keys^(x))) => (keys^(ret) s= (old(keys^(x)) setminus (singleton k)))) 
                  & ((~ (k i-in old(keys^(x)))) => (keys^(ret) s= old(keys^(x)))) )) */
{
  if (x == NULL) {
    return x;
  } else if (x->key == k) {
    DLNode * tmp = dll_delete(x->next, k);
    free(x);
    return tmp;
  } else {
    DLNode * tmp = dll_delete(x->next, k);
    x->next = tmp;
    if (tmp) tmp->prev = x;
    return x;
  }
}
