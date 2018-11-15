
#include <stdlib.h>

typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

BNode * bst_remove_root_rec(BNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if(x->left == NULL && x->right == NULL) {
    free(x);
    return NULL;
  } else if (x->left == NULL) {
    BNode * right = x->right;
    free(x);
    return right;
  } else if (x->right == NULL) {
    BNode * left = x->left;
    free(x);
    return left;
  } else {
    BNode * right = x->right;
    BNode * left = x->left;

    BNode * right_left = right->left;
    BNode * right_right = right->right;

    x->right = right_left;

    BNode * tmp = bst_remove_root_rec(x);

    right->left = tmp;
    
    return right;

  }
}
