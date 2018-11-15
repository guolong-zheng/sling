
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} SNnode;

SNnode * find_last_sorted(SNnode * l);

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

