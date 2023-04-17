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
BNode * bst_insert_rec(BNode * x, int k)
  /*D_requires (bst^(x) & (~ (k i-in keys^(x)))) */
  /*D_ensures  (bst^(ret) & (keys^(ret) s= (old(keys^(x)) union (singleton k)))) */
{

  if (x == NULL) {
    BNode * leaf = (BNode *) malloc(sizeof(BNode));
    _(assume leaf != NULL)

    leaf->key   = k;
    leaf->left  = NULL;
    leaf->right = NULL;

    return leaf;
  } else if (k < x->key) {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_rec(l, k);

    x->left = tmp;

    return x;
  } else {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_rec(r, k);
    
    x->right = tmp;

    return x;
  } 
}
