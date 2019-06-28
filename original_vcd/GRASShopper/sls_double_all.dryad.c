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
Node * sls_double_all(Node * lst)
  /*D_requires sorted-sll^(lst) */
  /*D_ensures  (sorted-sll^(lst) * sorted-sll^(ret)) */
{
  if (lst == NULL) {
    return NULL;
  } 

  Node * curr = lst;
  Node * cp = NULL;
  Node * res = (Node *) malloc(sizeof(Node));  
  _(assume res != NULL)
  cp = res;
  int curr_key = curr->key;
  cp->key = _(unchecked) (2 * curr_key);
  cp->next = NULL;
  while(curr->next != NULL) 
    /*D_invariant (((((curr |-> int key: ky) * true) & sorted-sll^(lst)) 
                   & ((sorted-lseg^(lst, curr) & (lseg-keys^(lst, curr) set-le ky)) * sorted-sll^(curr))) 
                 * ((sorted-sll^(res) & (((cp |-> loc next: nil; int key: ck) * true) & (ck i= (ky + ky)))) 
                    & (sorted-lseg^(res, cp) & (lseg-keys^(res, cp) set-le (ky + ky))) * sorted-sll^(cp)))  */
  {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    _(assume new_cp != NULL)
    old_cp->next = cp;
    curr = curr->next;
    curr_key = curr->key;
    cp->key = _(unchecked)(2 * curr_key);
    cp->next = NULL;
  }
  return res;
}
