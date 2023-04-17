#include "stdhipmem.h"


int treap_find_rec(BNode * x, int k)
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
        int r = treap_find_rec(x->left, k);
        return r;
      } else {
        int r = treap_find_rec(x->right, k);
        return r;
    }
  }
}
