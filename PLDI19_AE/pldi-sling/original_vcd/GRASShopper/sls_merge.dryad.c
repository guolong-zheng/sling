// ---- Definitions for GRASShopper examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

/*D_defs
define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * sll^(nxt))  
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (keys^(x) s= emptyset)) | ((~ (x l= nil)) & (~ (keys^(x) s= emptyset)))));

define pred sorted-sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * 
      (sorted-sll^(nxt) & (ky le-set keys^(nxt)))
      )  
  )
  axiom: (sorted-lseg^(x, x) * sll^(x));
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define relation lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * (lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))  
  ) 
  axiom: ( (((head l= tail) => (emp & (lseg-keys^(head, tail) s= emptyset))) & ((tail l= nil) => (sll^(head) & (keys^(head) s= lseg-keys^(head, tail))))) &
  ( (sll^(tail) -* (sll^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * sll^(tn))) ) ) ;

define relation sorted-lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * (sorted-lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))  
  ) 
  axiom: ( lseg^(head, tail) &
    ( ((tail l= nil) => sorted-sll^(head)) &
  ( (sorted-sll^(tail) -* ((lseg-keys^(head, tail) le keys^(tail)) => sorted-sll^(head))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* (((lseg-keys^(head, tail) set-le tk) * true) => (sorted-lseg^(head, tn) * sll^(tn)))) ) ) ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case (head l= tail) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;
*/
// -----------------------------------------------

_(dryad)
Node * merge(Node * a, Node * b) 
  /*D_requires (sorted-sll^(a) * sorted-sll^(b)) */
  /*D_ensures  sorted-sll^(ret) */
{

  Node * res = NULL;
  if (a == NULL) {
    return b;
  } else if (b == NULL) {
    return a;
  } else if (a->key <= b->key) {
    res = a;
    a = a->next;
  } else {
    res = b;
    b = b->next;
  }

  Node * last;
  last = res;

  while(a != NULL || b != NULL) 
    /*D_invariant (((((last |-> loc next: a; int key: lky) | (last |-> loc next: b; int key: lky))
                    * (sorted-lseg^(res, last) & (lseg-keys^(res, last) set-le lky)))
                   * (sorted-sll^(a) & (lky le-set keys^(a))))
                  * (sorted-sll^(b) & (lky le-set keys^(b)))) */
   {
    if (a == NULL || (b != NULL && a->key > b->key)) {
      last->next = b;
      last = b;
      b = b->next;
    } else {
      last->next = a;
      last = a;
      a = a->next;
    }
  }

  return res;
}

