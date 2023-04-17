#include "stdhipmem.h"



CNode * lseg_insert_back(CNode * hd, CNode * tl)
{
  CNode * next = hd->next;

	if (next == NULL) return next;
	if (next == tl) {
		free(hd);
		return next;
	} else {
		CNode * hd_next = lseg_insert_back(next, tl);
		hd->next = hd_next;
		return hd;
	}
}

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
		tl->next = x;
		x->next = tl;
		
		return tl;
	} else {
		CNode * tl = lseg_insert_back(next, x);
		x->next = tl;
		return tl;
	}
}

