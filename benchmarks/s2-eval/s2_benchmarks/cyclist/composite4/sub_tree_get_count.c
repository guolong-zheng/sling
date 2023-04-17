#include "stdhipmem.h"

int subtree_get_count(struct node *node)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  int result = 0;
  if (node != NULL) { result = node->count; }
  //post
  return result;
}


