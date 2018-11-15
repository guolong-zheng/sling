
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * sll_insert_back(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key  = k;	
		tail->next = NULL;
		return tail;
	} else {
		SNnode * tmp = sll_insert_back(x->next, k);
		x->next = tmp;
		return x;
	}
}
