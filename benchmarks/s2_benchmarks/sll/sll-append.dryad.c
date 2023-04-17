#include "stdhipmem.h"

SNnode * sll_append(SNnode * x1, SNnode * x2)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x1 == NULL) {
		return x2;
	} else {
		SNnode * tmp = sll_append(x1->next, x2);
		x1->next = tmp;
		return x1;
	}
	
}
