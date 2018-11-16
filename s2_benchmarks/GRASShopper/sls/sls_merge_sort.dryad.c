#include "stdhipmem.h"


Node * merge_sort(Node * lst) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * lst1 = split(lst);
  Node * a = merge_sort(lst1);
  Node * b = merge_sort(lst);
  return merge(a, b);
}
