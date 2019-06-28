#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/

int sll_find(struct node * x, int k)
/*@
 requires x::ll<>
 ensures x::ll<>;
 */
{
	if (x == NULL) {
		return -1;
	} else if (k == x->key) {
		return 1;
	} else {
                struct node * x_next = x->next;
		int res = sll_find(x_next, k);
		return res;
	}	
}
