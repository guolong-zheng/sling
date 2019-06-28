#include "stdhipmem.h"

struct node * makeNode()
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
    //pre
	struct node * n = malloc(sizeof(struct node));
	n->m = 0;
	n->c = 0;
	n->l = 0;
	n-> r = 0;
    //post
	return n;
}
