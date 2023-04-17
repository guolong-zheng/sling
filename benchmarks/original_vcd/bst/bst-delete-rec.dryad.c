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

BNode * bst_remove_root(BNode * x)
  /*D_requires  (((x |-> loc left: lft; loc right: rgt; int key: ky) * 
     (bst^(lft) * bst^(rgt))) & (keys^(lft) lt keys^(rgt))) */
  /*D_ensures (bst^(ret) & (keys^(ret) s= (old(keys^(lft)) union old(keys^(rgt)))))*/
;

_(dryad)
BNode * bst_delete_rec(BNode * x, int k)
  /*D_requires (bst^(x) & & (k i-in keys^(x))) */
  /*D_ensures  (bst^(ret) & (keys^(ret) s= (old(keys^(x)) setminus (singleton k)))) */
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
