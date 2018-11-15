
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * sorted_insert(SNnode *x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		
		tail->key = k;
		tail->next = NULL;

		return tail;
	} 
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
		return x;
	} 
	else {

		SNnode * head = (SNnode *) malloc(sizeof(SNnode));

		head->key = k;
		head->next = x;

		return head;
	}
}

