#include "stdhip.h"

/*pred definition:
data node {
     int key;
     node next; };
*/

struct node {
  int key;
  struct node * next;
} SNnode;

/*@
ll<> == emp & self=null
or (exists v, y: self::node<v, y> * y::ll<>);
*/


struct node * sll_insert_front(struct node * x, int k)
/*@
      requires x::ll<>
      ensures (exists h: x::ll<> * h::node<_, x> & h=res);
*/
{
    // ll(x)
	struct node * head =  malloc(sizeof(struct node));
	head->key = k;
	head->next = x;
    // ll(x) * head:node->node{fv!57, x} & head=res
	return head;
}
