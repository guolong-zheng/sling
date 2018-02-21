#include "g_list.h"
#include <stdlib.h>

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

int g_list_index(DLNode * list, int data)
  /*D_requires (dll^(list) & length^(list) < INT_MAX)*/
  /*D_ensures  (dll^(old(list))
             & ((((lseg^(old(list), list) & (lseg-length^(old(list), list) i= ret)) * dll^(list)) & (data i-in keys^(old(list))))
               | ((ret i= -1) & (~ (data i-in keys^(old(list))))))) */
{
  int i;

  i = 0;
  while(list != NULL)
    /*D_invariant (dll^(old(list))
                  & ((lseg^(old(list), list)
                     & ((~ (data i-in lseg-keys^(old(list), list)))
                        & (lseg-length^(old(list), list) i= i & ((i < INT_MAX) & (i >= 0)))))
                    * dll^(list))) */
   {
    if (list->key == data) {
      return i;
    }
    i ++;
    list = list->next;
   }
  return -1;
}

int main(){
    DLNode * root = create_list(5);
    int res = g_list_index(root, rand());

    return 0;
}
