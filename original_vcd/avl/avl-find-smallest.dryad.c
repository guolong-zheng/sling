// ---- Commmon definitions for avl examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag a_node */
struct a_node {
  struct a_node * left;
  struct a_node * right;
  int key;
  int height;
} AVLNode;

/*D_defs
define pred avl^(x): 
  ( ((x l= nil) & emp) |
    (
        (x |-> loc left: lft; loc right: rgt; int key: ky; int hight: hgt) * 
        (
   (
    (avl^(lft) & (keys^(lft) set-lt ky)) *
    (avl^(rgt) & (ky lt-set keys^(rgt)))
   ) &
   (
    ((height^(lft) i= height^(rgt)) & ((hgt i= (height^(lft) + 1)) * true))      |
    ( ((height^(lft) i= (height^(rgt) + 1)) & ((hgt i= (height^(rgt) + 2)) * true) ) |
    ((height^(rgt) i= (height^(lft) + 1)) & ((hgt i= (height^(lft) + 2)) * true) ) )
  )
       )
    )
  ) ;

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc left: lft; loc right: rgt; int key: ky; int hight: hgt) * true): 
    ((singleton ky) union (keys^(lft) union keys^(rgt)));
   default: emptyset
  ) ;

define int-fun height^(x):
  (case (x l= nil): 0;
   case (((x |-> loc left: lft; loc right: rgt; int key: ky; int hight: hgt) * true) &
  ((height^(lft) < height^(rgt)) * true)): 
    (height^(rgt) + 1);
   default: (height^(lft) + 1)
  ) ;
*/
// -----------------------------------------------


_(dryad)
int avl_find_smallest(AVLNode * x)
  /*D_requires (avl^(x) & (~ (x l= nil))) */
  /*D_ensures ((avl^(x) & (~ (x l= nil)))
              & ((ret le-set keys^(x)) & (ret in old(keys^(x))))) */
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		return r;
	}
}

