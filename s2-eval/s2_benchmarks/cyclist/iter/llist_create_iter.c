#include "stdhipmem.h"

struct iter *llist_create_iter(struct llist *l)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
    //pre
    struct iter *i = 0;
    struct node *f = 0;
    i = malloc(sizeof(struct iter));
    
    f = l->first;
    i->current = f;
    //post
    return i;
}


