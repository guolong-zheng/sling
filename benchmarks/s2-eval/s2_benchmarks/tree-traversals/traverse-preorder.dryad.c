#include "stdhipmem.h"


int preorder(TNode * x, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	if (x == NULL) {
		return n;
	} else {
		x->key = n;
		int n1 = n + 1;
		int n2 = preorder(x->left, n1);
		int n3 = preorder(x->right, n2);

		return n3;
	}
}

