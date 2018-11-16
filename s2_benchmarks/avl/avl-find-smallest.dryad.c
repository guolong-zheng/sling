#include "stdhipmem.h"



int avl_find_smallest(AVLNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		return r;
	}
}

