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
 )
 
 define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;
*/
// --------------------------------------------------------------

_(dryad)
DLNode * dll_insert_front(DLNode * x, int k) 
  /*D_requires dll^(x) */
  /*D_ensures (dll^(ret) & (keys^(ret) s= (old(keys^(x)) union (singleton k)))) */
{
  if (x == NULL) {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    _(assume head != NULL)
    head->key = k;
    head->next = NULL;
    head->prev = NULL;
    return head;
  } else {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    _(assume head != NULL)
    head->key = k;
    head->next = x;
    x->prev = head;
    return head;
  }
}


