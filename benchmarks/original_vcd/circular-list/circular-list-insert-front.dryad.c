// ---- Commmon definitions for circular list examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} CNode;

/*D_defs 
  define relation lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
  ((head |-> loc next: nxt) * lseg^(nxt, tail))  
  ) ;
*/
// ---------------------------------------------------------

_(dryad)
CNode * circular_list_insert_front(CNode * x)
  /*D_requires ((x |-> loc next: nxt) * lseg^(nxt, x)) */
  /*D_ensures  ((x |-> loc next: ret) * lseg^(ret, x)) */
{
	CNode * tmp = x->next;
	CNode * hd = (CNode *) malloc(sizeof(CNode)) ;
	_(assume hd != NULL)
	hd->next = tmp;
	x->next = hd; 
	return hd;
}
