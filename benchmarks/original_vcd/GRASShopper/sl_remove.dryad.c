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
Node * sl_remove(Node * lst)
  /*D_requires lseg^(lst, nil) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (lst == NULL) {
    return NULL;
  } else {
    int nondet;
    Node * curr = lst;
    while(nondet && curr->next != NULL)
      /*D_invariant (((~ (curr l= nil)) & lseg^(curr, nil)) * lseg^(lst, curr)) */
    {
      nondet = havoc();
      curr = curr->next;
    }
    Node * tmp = curr->next;
    if (tmp != NULL) {
      Node * tmp_next = tmp->next;
      curr->next = tmp_next;
      free(tmp);
    }
    return lst;
  }
}
