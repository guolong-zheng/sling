#include "stdhipmem.h"



SNnode * sll_copy(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x == NULL) {
		return x;
	} else {
		SNnode * tmp = sll_copy(x->next, k);
		SNnode * new_node = (SNnode *) malloc(sizeof(SNnode));
    int tmp_key = x->key;
		new_node->key = tmp_key;
		new_node->next = tmp;
		return new_node;
	}
}

