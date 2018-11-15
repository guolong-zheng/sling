
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

int sll_find(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x == NULL) {
		return -1;
	} else if (k == x->key) {
		return 1;
	}	else {
    SNnode * x_next = x->next;
		int res = sll_find(x_next, k);
		return res;
	}	
}
