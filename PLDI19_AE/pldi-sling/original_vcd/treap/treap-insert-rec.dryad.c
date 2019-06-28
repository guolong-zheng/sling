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
BNode * treap_insert_rec(BNode * x, int k, int p)
  /*D_requires (treap^(x) & (~ ((k i-in keys^(x)) | (p i-in priorities^(x))))) */ 
  /*D_ensures (treap^(ret) 
          & ((keys^(ret) s= (old(keys^(x)) union (singleton k))) 
          & (priorities^(ret) s= (old(priorities^(x)) union (singleton p))))) */
{

  if (x == NULL) {
    BNode * leaf = (BNode *) malloc(sizeof(BNode));
    _(assume leaf != NULL)

    leaf->key = k;
    leaf->prio = p;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
  } else {

    if (k < x->key) {
      BNode * xr = x->right;
      BNode * xl = x->left;
      BNode * tmp = treap_insert_rec(xl, k, p);

      if (tmp->prio <= x->prio) {

        x->left = tmp;

        return x;
      } else {      
        BNode * lr = tmp->right;

        x->left = lr;

        tmp->right = x;

        return tmp;
      }
    } else {
      BNode * xr = x->right;
      BNode * xl = x->left;
      BNode * tmp = treap_insert_rec(xr, k, p);

      if (tmp->prio <= x->prio) {

        x->right = tmp;

        return x;
      } else {
        BNode * rl = tmp->left;

        x->right = rl;

        tmp->left = x;
        
        return tmp;
      }
    } 
  }
}