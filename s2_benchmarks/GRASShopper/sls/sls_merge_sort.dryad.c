
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * split(Node * x)
  /*D_requires sll^(x) */
  /*D_ensures (old(sll^(x)) * sll^(result)) */
;

Node * merge(Node * a, Node * b) 
  /*D_requires (sorted-sll^(a) * sorted-sll^(b)) */
  /*D_ensures  sorted-sll^(ret) */
;

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
