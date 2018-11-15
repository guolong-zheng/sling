
#include <stdlib.h>

typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

BNode * bst_find_iter(BNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  BNode * curr = x;
  while(curr != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (curr->key == k) {
      return curr;
    } else if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  
  return curr;
}

