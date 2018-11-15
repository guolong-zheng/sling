
#include <stdlib.h>

typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

int bst_find_rec(BNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL) {
    return 0;
  } else {
      if (k == x->key) {
        return 1;
      } else if (k < x->key) {
        int r = bst_find_rec(x->left, k);
        return r;
      } else {
        int r = bst_find_rec(x->right, k);
        return r;
    }
  }
}
