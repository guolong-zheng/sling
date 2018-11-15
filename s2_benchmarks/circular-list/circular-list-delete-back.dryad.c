
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} CNode;

CNode * lseg_delete_back(CNode * hd, CNode * tl)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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


CNode * circular_list_delete_back(CNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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
