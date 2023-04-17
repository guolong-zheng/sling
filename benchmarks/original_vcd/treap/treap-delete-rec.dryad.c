// ---- Commmon definitions for treap examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
  int prio;
} BNode;

/*D_defs 
define pred treap^(x): 
  ( ((x l= nil) & emp) |
    ((x |-> loc left: lft; loc right: rgt; int key: ky; int priority: pt) * 
  (((treap^(lft) & ((keys^(lft) set-lt ky) & (priorities^(lft) set-lt pt))) *
    (treap^(rgt) & ((ky lt-set keys^(rgt)) & (priorities^(rgt) set-lt pt)))) & 
   ((priorities^(lft) intersection priorities^(rgt)) s= emptyset)))
  ) ;

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    ((singleton ky) union (keys^(lft) union keys^(rgt)));
   default: emptyset
  ) ;

define set-fun priorities^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc left: lft; loc right: rgt; int priority: pt) * true): 
    ((singleton pt) union (priorities^(lft) union priorities^(rgt)));
   default: emptyset
  ) ;
*/
// -------------------------------------------------

BNode * treap_remove_root(BNode * x)
  /*D_requires (((x |-> loc left: lft; loc right: rgt; int key: ky; int priority: pt) 
               * ((treap^(lft)) *(treap^(rgt)))) 
                & ((keys^(lft) lt keys^(right)) & ((priorities^(left) intersection priorities^(right)) s= emptyset))) */
  /*D_ensures (treap^(ret) & ((keys^(ret) s= (old(keys^(lft)) union old(keys^(rgt)))) & 
         (priorities^(ret) s= (old(priorities^(lft)) union old(priorities(rgt)))))) */
;

_(dryad)
BNode * treap_delete_rec(BNode * x, int k)
  /*D_requires (treap^(x) & (k i-in keys^(x))) */
  /*D_ensures  ((treap^(ret) & (keys^(ret) s= (old(keys^(x)) setminus (singleton k)))) & 
    (priorities^(ret) s-subset old(priorities^(x)))) */
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
