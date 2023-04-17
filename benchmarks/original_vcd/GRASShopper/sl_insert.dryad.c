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

_(pure) int havoc();

_(dryad)
Node * sl_insert(Node * lst, Node * elt)
  /*D_requires (lseg^(lst, nil) * ((elt |-> loc next: nil))) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (lst == NULL) {
    return elt;
  } else {
    int nondet;
    Node * curr = lst;
    while(nondet && curr->next != NULL)
      /*D_invariant (((~ (curr l= nil)) & lseg^(curr, nil)) * (lseg^(lst, curr))) */
    {
      nondet = havoc();
      curr = curr->next;
    }
    Node * curr_next = curr->next;
    elt->next = curr_next;
    curr->next = elt;
    return lst;
  }
}
