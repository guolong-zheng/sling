
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * merge_sort_copy(SNnode * l1, SNnode * l2)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	if (l1 == NULL) {
		return l2;
	} else if (l2 == NULL) {
		return l1;
	} else {
		if (l1->key <= l2->key) {
			SNnode * tl = merge_sort_copy(l1->next, l2);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
      int l1_key = l1->key;
			nl->key  = l1_key;
			nl->next = tl;
			return nl;	
		} else {
			SNnode * tl = merge_sort_copy(l1, l2->next);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));   
      int l2_key = l2->key;
			nl->key = l2_key;
			nl->next = tl;

			return nl;
		}
	}
}
