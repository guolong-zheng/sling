#include "stdhip.h"

struct node {
  int key;
  struct node * next;
};

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/


struct node * sll_delete_all(struct node * x, int k)
/*@
 requires x::ll<>
 ensures (exists k: k::ll<> & k = res);
 */
{
	if (x == NULL) {
		return x;
	} else if (x->key == k) {
		struct node * tmp = sll_delete_all(x->next, k);
		free(x);
		return tmp;
	} else {
		struct node * tmp = sll_delete_all(x->next, k);
		x->next = tmp;
		return x;
	}
}

