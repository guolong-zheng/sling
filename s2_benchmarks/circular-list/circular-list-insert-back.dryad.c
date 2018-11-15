
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} CNode;

CNode * lseg_insert_back(CNode * hd, CNode * tl)
  /*D_requires (lseg^(hd, tl) & (~ (hd l= tl))) */
  /*D_ensures lseg^(ret, tl) */
;

CNode * circular_list_insert_back(CNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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

