#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} ;

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/

struct node * sll_insert_back(struct node * x, int k)
/*@
 requires x::ll<>
 ensures (exists k: k::ll<> & k = res);
 */
{
	if (x == NULL) {
		struct node * tail = (struct node *) malloc(sizeof(struct node));
		tail->key  = k;	
		tail->next = NULL;
		return tail;
	} else {
		struct node * tmp = sll_insert_back(x->next, k);
		x->next = tmp;
		return x;
	}
}
