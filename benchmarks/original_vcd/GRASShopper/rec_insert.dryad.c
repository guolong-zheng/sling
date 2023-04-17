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
Node * rec_insert(Node * lst, Node * elt)
  /*D_requires (lseg^(lst, nil) * ((elt |-> loc next: nil))) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (lst == NULL) {
    return elt; 
  } else {
    int nondet;
    if (nondet) {
      elt->next = lst;
      return elt;
    } else {
      Node * n1 = lst->next;
      Node * n2 = rec_insert(n1, elt);
      lst->next = n2;
      return lst;
    }
  }
}
