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
  ) ; */
// -------------------------------------------------


_(dryad)
BNode * treap_remove_root_rec(BNode * x)
  /*D_requires (((x |-> loc left: lft; loc right: rgt; int key: ky; int priority: pt) 
               * ((treap^(lft)) *(treap^(rgt)))) 
                & ((keys^(lft) lt keys^(right)) & ((priorities^(left) intersection priorities^(right)) s= emptyset))) */
  /*D_ensures (treap^(ret) & ((keys^(ret) s= (old(keys^(lft)) union old(keys^(rgt)))) & 
         (priorities^(ret) s= (old(priorities^(lft)) union old(priorities(rgt)))))) */
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

