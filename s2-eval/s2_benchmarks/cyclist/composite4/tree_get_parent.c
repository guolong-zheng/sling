#include "stdhipmem.h"

struct node *tree_get_parent(struct node *node)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  struct node *p = node->parent;
  //post
  return p;
}



