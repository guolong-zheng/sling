#include "stdhipmem.h"



SNnode * sll_insert_back(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key  = k;	
		tail->next = NULL;
		return tail;
	} else {
		SNnode * tmp = sll_insert_back(x->next, k);
		x->next = tmp;
		return x;
	}
}
