// ---- Definitions for glib/gslist examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

/*D_defs
define pred list^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * list^(nxt))
  ) ;
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define relation lseg^(head, tail): 
  ( 
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * lseg^(nxt, tail))  
  ) 
axiom: ( 
      (list^(tail) -* (list^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))))) &
      (((tail |-> loc next: virtual tn; int key: virtual tk) * list^(tn)) -* ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * list^(tn))) 
     ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case ((head l= tail) | ((head l= nil) & (tail l= nil))) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;
*/
// ------------------------------------------------

Node * g_slist_last(Node * list)
  /*D_requires list^(x) */
  /*D_ensures ((list^(old(x)) & (old(keys^(x)) s= keys^(old(x)))) & (((old(x) l= nil) => (ret l= nil)) &
                      ((~ (old(x) l= nil)) => (lseg^(old(x), ret) 
                                              * ((ret |-> loc next: temp; int key: kx) & (temp l= nil)))))) */
;

_(dryad)
Node * g_slist_concat(Node * list1, Node * list2)
  /*D_requires (list^(list1) * list^(list2) */
  /*D_ensures (list^(ret) & (keys^(ret) s= (old(keys^(list1)) union old(keys^(list2))))) */
{
  if (list2 != NULL) {
    if (list1 != NULL) {
      Node * last = g_slist_last(list1);
      last->next = list2;
    } else {
      list1 = list2;
    }
  }
  return list1;
}
