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
Node * rec_reverse_acc(Node * curr, Node * rev)
  /*D_requires (lseg^(rev, nil) * lseg^(curr, nil)) */
  /*D_ensures  lseg^(ret, nil) */
{
  if (curr == NULL) {
    return rev;
  } else {
    Node * tmp = curr->next;
    curr->next = rev;
    Node * ret = rec_reverse_acc(curr, tmp);
    return ret;
  }
}

_(dryad)
Node * rec_reverse(Node * lst) 
  /*D_requires lseg^(lst, nil) */
  /*D_ensurs   lseg^(ret, nil) */
{
  return rec_reverse_acc(lst, NULL);
}
