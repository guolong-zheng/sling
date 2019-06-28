#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/


struct node * sll_copy(struct node * x, int k)
/*@
 requires x::ll<>
 ensures (exists k: K::ll<> & k=res);
 */
{
	if (x == NULL) {
		return x;
	} else {
		struct node * tmp = sll_copy(x->next, k);
		struct node * new_node = (struct node *) malloc(sizeof(struct node));
                int tmp_key = x->key;
		new_node->key = tmp_key;
		new_node->next = tmp;
		return new_node;
	}
}

