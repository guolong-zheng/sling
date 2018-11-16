#include "stdhipmem.h"



SNnode * sorted_insert(SNnode *x, int k)
{

	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		
		tail->key = k;
		tail->next = NULL;

		return tail;
	} 
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
		return x;
	} 
	else {

		SNnode * head = (SNnode *) malloc(sizeof(SNnode));

		head->key = k;
		head->next = x;

		return head;
	}
}

SNnode * insertion_sort_copy(SNnode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (l == NULL) {
		return l;
	} else {
		SNnode * tl = insertion_sort_copy(l->next);

		SNnode * nl = sorted_insert(tl, l->key);
		return nl;
	}
}

