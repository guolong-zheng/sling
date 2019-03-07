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
CNode * lseg_delete_back(CNode * hd, CNode * tl)
  /*D_requires  ((~(hd l= nil)) & lseg^(hd, tl)) */
  /*D_ensures lseg^(ret, tl) */
{
	CNode * next = hd->next;

	if (next == NULL) return next;
	if (next == tl) {
		free(hd);
		return next;
	} else {
		CNode * hd_next = lseg_delete_back(next, tl);
		hd->next = hd_next;
		return hd;
	}
}

_(dryad)
CNode * circular_list_delete_back(CNode * x)
  /*D_requires ((x |-> loc next: nxt) * lseg^(nxt, x)) */
  /*D_ensures ((emp & ((x l= nxt) => (ret l= nil))) |
       ((~(x l= nxt)) => ((x |-> loc next: ret) * lseg^(ret, x))) */
{
	CNode * next = x->next;
	if (next == x) {
		free(next);
		return NULL;
	} else {
		CNode * hd_next = lseg_delete_back(next, x);
		x->next = hd_next;
		return hd_next;
	}
}
