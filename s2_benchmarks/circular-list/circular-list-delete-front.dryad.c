
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} CNode;

CNode * circular_list_delete_front(CNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	CNode * next = x->next;

	if (next == x) {
		free(next);
		return NULL;
	} else {
		CNode * next_next = next->next;
		free(next);
		x->next = next_next;
		return next_next;
	}
}

