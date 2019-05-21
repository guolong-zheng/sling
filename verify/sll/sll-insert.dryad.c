#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
sll<> == emp & self=null
or (exists k, n: self::node<k,n> * n::sll<>);
*/

struct node * sll_insert(struct node * x, int k)
/*@
 requires x::sll<>
 ensures (exists fv1: fv1::sll<>);
 */
{
	if (x == NULL) {
		struct node * leaf = (struct node * ) malloc(sizeof(struct node ));
		leaf->key = k;
		leaf->next = NULL;
		return leaf;

	} else if (k > x->key) {
		struct node *  tmp = sll_insert(x->next, k);
		x->next = tmp;
		return x;
	}	else {	
		struct node *  new_root = (struct node * ) malloc(sizeof(struct node ));
		new_root->key = k;
		new_root->next = x;
		return new_root;
	}
}


