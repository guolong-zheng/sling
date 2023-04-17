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
BNode * bst_remove_root_rec(BNode * x)
  /*D_requires  (((x |-> loc left: lft; loc right: rgt; int key: ky) * 
     (bst^(lft) * bst^(rgt))) & (keys^(lft) lt keys^(rgt))) */
  /*D_ensures (bst^(ret) & (keys^(ret) s= (old(keys^(lft)) union old(keys^(rgt)))))*/
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