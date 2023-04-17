#include "stdhipmem.h"

int iter_next(struct iter *i)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
    //pre
    struct node *c = i->current;
    int value = c->value;
    struct node *n = c->next;
    i->current = n;
    //post
    return value;
}


