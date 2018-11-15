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

CNode * lseg_insert_back(CNode * hd, CNode * tl)
  /*D_requires (lseg^(hd, tl) & (~ (hd l= tl))) */
  /*D_ensures lseg^(ret, tl) */
;

_(dryad)
CNode * circular_list_insert_back(CNode * x)
  /*D_requires ((x |-> loc next: nxt) * lseg^(nxt, x)) */
  /*D_ensures ((x |-> loc next: ret) * lseg^(ret, x)) */

{
	CNode * next = x->next;

	if (next == x) {
		CNode * tl = (CNode *) malloc(sizeof(CNode));
		_(assume tl != NULL)
		tl->next = x;
		x->next = tl;
		
		return tl;
	} else {
		CNode * tl = lseg_insert_back(next, x);
		x->next = tl;
		return tl;
	}
}

