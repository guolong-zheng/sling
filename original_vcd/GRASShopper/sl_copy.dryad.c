// ---- Definitions for GRASShopper examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

/*D_defs
define pred list^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt) * list^(nxt))
  ) ;
  

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

_(dryad)
Node * sl_copy(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures (lseg^(lst, nil) * lseg^(ret, nil)) */
{

  Node * curr = lst;
  Node * cp = NULL;
  while(curr != NULL) 
    /*D_invariant ((lseg^(lst, curr) * lseg^(curr, nil)) * lseg^(cp, nil)) */
  {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    _(assume cp != NULL)
    cp->next = old_cp;
    curr = curr->next;
  }
  return cp;
}
