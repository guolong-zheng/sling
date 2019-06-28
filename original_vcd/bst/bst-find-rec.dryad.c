// ---- Commmon definitions for bst examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

/*D_defs 
define pred bst^(x): 
  ( ((x l= nil) & emp) |
    ((x |-> loc left: lft; loc right: rgt; int key: ky) * ((bst^(lft) & (keys^(lft) set-lt ky)) * (bst^(rgt) & (ky lt-set keys^(rgt)))))  
  );

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    ((singleton ky) union (keys^(lft) union keys^(rgt)));
   default: emptyset
  ) ;
*/
// -----------------------------------------------

_(dryad)
int bst_find_rec(BNode * x, int k)
  /*D_requires bst^(x)) */
  /*D_ensures  (((ret i= 1) & (k i-in old(keys^(x)))) | ((ret i= 0) & (~ (k i-in old(keys^(x)))))) */
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
