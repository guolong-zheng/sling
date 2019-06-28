#include "stdhip.h"

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
ls<y> == emp & self=y
or (exists u, v: self::node<u, v> * v::ls<y> );

ll<> == emp & self=null
or (exists u, v: self::node<u,v> * v::ll<>);
*/

struct node * concat_sorted(struct node * x, struct node * y)
/*@
   requires x::ll<> * y::ll<>
   ensures x::ll<> & x=res;
 */
{
//   requires x::ls<null> * y::ls<null>
//   ensures x::ls<y> * y::ls<null>;
	if (y != NULL) {
		if (x != NULL) {
			struct node * last = find_last_sorted(x);
			last->next = y;
		} else {
			x = y;
		}
	} 
	return x;
}

struct node * find_last_sorted(struct node * l)
/*@
  requires l::ll<>
  ensures (exists curr: curr::node<_,null> & curr=res);
*/;

/*
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
*/
