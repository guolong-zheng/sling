#include "stdhipmem.h"



CNode * circular_list_insert_front(CNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	CNode * tmp = x->next;
	CNode * hd = (CNode *) malloc(sizeof(CNode)) ;
	hd->next = tmp;
	x->next = hd; 
	return hd;
}
