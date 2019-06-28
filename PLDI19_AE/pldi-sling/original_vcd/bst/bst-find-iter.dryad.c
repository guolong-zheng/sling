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
BNode * bst_find_iter(BNode * x, int k)
  /*D_requires  bst^(x) */
  /*D_ensures (bst^(x) & ((ret l= nil) | ((ret |-> int key: k) * true))) */
{
  BNode * curr = x;
  while(curr != NULL)
    /*D_invariant ((bst^(x) & (bst^(curr) * true)) 
        & ((k i-in keys^(x)) <=> ((k i-in keys^(curr)) * true))) */
  {
    if (curr->key == k) {
      return curr;
    } else if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  
  return curr;
}

