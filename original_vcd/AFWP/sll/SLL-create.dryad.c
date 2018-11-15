// ---- Definitions for AFWP examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

/*D_defs
define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt) * sll^(nxt))
  ) ;
  

define relation lseg^(head, tail): 
  ( 
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) | 
          ((head |-> loc next: nxt) * lseg^(nxt, tail))  
  ) 
axiom: ( 
      (sll^(tail) -* sll^(head)) &
      (((tail |-> loc next: virtual tn) * sll^(tn)) -* ((lseg^(head, tn) * sll^(tn)))) 
     ) ;
*/

// ----------------------------------------

_(dryad)
Node * create(unsigned sz)
  /*D_ensures sll^(ret) */
{
  Node * h = NULL;
  while(sz > 0) 
    /*D_invariant sll^(h) */
  {
    sz --;
    Node * e = (Node *)malloc(sizeof(Node));
    _(assume e != NULL)

    e->next = h;
    h = e;
  }
  return h;
}
