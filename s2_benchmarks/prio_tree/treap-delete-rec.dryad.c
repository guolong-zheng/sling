
#include <stdlib.h>

typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
  int prio;
} BNode;

BNode * treap_remove_root(BNode * x);

BNode * treap_delete_rec(BNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if(x->key == k) {
    BNode * r = treap_remove_root(x);
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
