#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
ls<y> == emp & self=y
or (exists u, v: self::node<u, v> * v::ls<y> );
*/


struct node * find_last_sorted(struct node * l)
/*@
 requires l::ls<null>
 ensures (exists curr: curr=null or curr::node<_,null>);
 */
{
  struct node * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
		{ 
			curr = curr->next;
		}
	}
	return curr;
}
