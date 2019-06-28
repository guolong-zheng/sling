#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/

struct node * sll_append(struct node * x1, struct node * x2)
/*@
 requires x1::ll<> * x2::ll<>
 ensures (exists x: x::ll<> & x = res);
 */
{
	if (x1 == NULL) {
		return x2;
	} else {
		struct node * tmp = sll_append(x1->next, x2);
		x1->next = tmp;
		return x1;
	}
	
}
