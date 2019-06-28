#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} ;

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/

struct node * sll_reverse(struct node * x)
/*@
  requires x::ll<>
  ensures (exists y: y::ll<> & res = y);
*/
{
	struct node * y = NULL;
        struct node * tmp = NULL;
	while (x != NULL)
	{
		tmp = x->next;
		x->next = y;
		y = x;
		x = tmp;
	}
	return y;
}
