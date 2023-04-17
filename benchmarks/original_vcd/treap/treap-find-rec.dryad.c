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
  ) ;*/
// -------------------------------------------------

_(dryad)
int treap_find_rec(BNode * x, int k)
  /*D_requires treap^(x) */
  /*D_ensures  (((ret i= 1) & (k i-in old(keys^(x)))) | ((ret i= 0) & (~ (k i-in old(keys^(x)))))) */
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