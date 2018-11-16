#include "stdhipmem.h"

BNode * treap_remove_root_rec(BNode * x)
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
    BNode * left  = x->left;

    if(left->prio <= right->prio) {
      BNode * right_left = right->left;
      BNode * right_right = right->right;
      BNode * left_left = left->left;
      BNode * left_right = left->right;
      x->right = right_left;
      BNode * tmp = treap_remove_root_rec(x);
      right->left = tmp;  
      return right;
    } else {
      BNode * right_left = right->left;
      BNode * right_right = right->right;
      BNode * left_left = left->left;
      BNode * left_right = left->right;

      x->left = left_right;

      BNode * tmp = treap_remove_root_rec(x);

      left->right = tmp;  
      return left;
    }
  }
}

BNode * treap_delete_rec(BNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if(x->key == k) {
    BNode * r = treap_remove_root_rec(x);
    return r;
  } else if (k < x->key) {
    
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = treap_delete_rec(xl, k);

    x->left = l;

    return x;
  } else {
    
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = treap_delete_rec(xr, k);

    x->right = r;

    return x;
  }
}
