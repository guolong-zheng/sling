
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

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

