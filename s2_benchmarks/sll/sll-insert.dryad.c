
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * sll_insert(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x == NULL) {
		SNnode * leaf = (SNnode *) malloc(sizeof(SNnode));
		
		leaf->key = k;
		leaf->next = NULL;
		return leaf;

	} else if (k > x->key) {
		SNnode * tmp = sll_insert(x->next, k);
		x->next = tmp;
		return x;
	}	else {	
		SNnode * new_root = (SNnode *) malloc(sizeof(SNnode));
		
		new_root->key = k;
		new_root->next = x;
		return new_root;
	}
}


