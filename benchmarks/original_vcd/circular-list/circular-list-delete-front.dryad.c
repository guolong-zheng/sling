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
CNode * circular_list_delete_front(CNode * x)
  /*D_requires ((x |-> loc next: nxt) * lseg^(nxt, x)) */
  /*D_ensures ((emp & ((x l= nxt) => (ret l= nil))) |
       ((~(x l= nxt)) => ((x |-> loc next: ret) * lseg^(ret, x)))) */
{
	CNode * next = x->next;

	if (next == x) {
		free(next);
		return NULL;
	} else {
		CNode * next_next = next->next;
		free(next);
		x->next = next_next;
		return next_next;
	}
}

