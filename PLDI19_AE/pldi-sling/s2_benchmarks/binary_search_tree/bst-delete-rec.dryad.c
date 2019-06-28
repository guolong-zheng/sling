#include "stdhipmem.h"



BNode * bst_remove_root(BNode * x)
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

    BNode * tmp = bst_remove_root(x);

    right->left = tmp;
    
    return right;

  }
}

BNode * bst_delete_rec(BNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if(x->key == k) {
    BNode * r = bst_remove_root(x);
    return r;
  } else if (k < x->key) {
    
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = bst_delete_rec(xl, k);

    x->left = l;

    return x;
  } else {
    
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = bst_delete_rec(xr, k);

    x->right = r;

    return x;
  }
}
