#include "stdhipmem.h"



int sorted_find(SNnode * l, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (l == NULL) {
		return -1;
	} else if (l->key == k) {
		return 1;
	} else {
		int res = sorted_find(l->next, k);
		return res;
	}
}

