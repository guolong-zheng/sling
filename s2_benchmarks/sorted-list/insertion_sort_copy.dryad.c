
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * sorted_insert(SNnode *x, int k);

SNnode * insertion_sort_copy(SNnode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (l == NULL) {
		return l;
	} else {
		SNnode * tl = insertion_sort_copy(l->next);

		SNnode * nl = sorted_insert(tl, l->key);
		return nl;
	}
}

