
#include <stdlib.h>
typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

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
