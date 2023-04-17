#include "stdhipmem.h"

/*
SNnode * find_last_sorted(SNnode * l)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
/*{
  SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
		{ 
			curr = curr->next;
		}
	}
	return curr;
}*/

SNnode * concat_sorted(SNnode * l1, SNnode * l2)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (l2 != NULL) {
		if (l1 != NULL) {
			SNnode * last = find_last_sorted(l1);
			last->next = l2;
		} else {
			l1 = l2;
		}
	} 
	return l1;
}

