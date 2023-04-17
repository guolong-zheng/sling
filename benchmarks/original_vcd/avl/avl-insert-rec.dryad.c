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

int avl_find_smallest(AVLNode * x)
  /*D_requires (avl^(x) & (~ (x l= nil))) */
  /*D_ensures ((avl^(x) & (~ (x l= nil)))
              & ((ret le-set keys^(x)) & (ret in old(keys^(x))))) */
;

AVLNode * avl_balance(AVLNode * x)
  /*D_requires ((((x |-> loc left: clft; loc right: crgt; int key: cky; int hight: chgt) 
                 * (((avl^(clft)) & (keys^(clft) set-lt cky)) * ((avl^(crgt)) & (cky lt-set keys^(crgt))))) 
                & ((height^(crgt) <= (height^(clft) + 2)) & (height^(clft) <= (height^(crgt) + 2)))) 
               & ((((crgt l= nil) | ((crgt |-> loc left: rgtlft; loc right: rgtrgt))) 
                  * ((clft l= nil) | ((clft |-> loc left: lftlft; loc right: lftrgt)))) * true)) */
  /*D_ensures ((avl^(ret) & (keys^(ret) s= ((singleton cky) union (old(keys^(clft)) union old(keys^(crgt)))))) & 
    (((((old(height^(crgt)) i= (old(height^(clft)) + 1)) & (height^(ret) i= (old(height^(crgt)) + 1))) 
      |((old(height^(clft)) i= (old(height^(crgt)) + 1)) & (height^(ret) i= (old(height^(clft)) + 1)))) 
      |((old(height^(clft)) i=  old(height^(crgt))     ) & (height^(ret) i= (old(height^(clft)) + 1)))) 
      
   |(((((old(height^(crgt)) i= (old(height^(clft)) + 2)) &    (old(height^(rgtlft)) i= old(height^(rgtrgt))))  & (height^(ret) i= (old(height^(crgt)) + 1))) 
     |(((old(height^(crgt)) i= (old(height^(clft)) + 2)) & (~ (old(height^(rgtlft)) i= old(height^(rgtrgt))))) & (height^(ret) i=  old(height^(crgt))    ))) 
     
    |((((old(height^(clft)) i= (old(height^(crgt)) + 2)) &    (old(height^(lftlft)) i= old(height^(lftrgt))))  & (height^(ret) i= (old(height^(clft)) + 1))) 
    | (((old(height^(clft)) i= (old(height^(crgt)) + 2)) & (~ (old(height^(lftlft)) i= old(height^(lftrgt))))) & (height^(ret) i=  old(height^(clft))    ))))))
  */
;


_(dryad)
AVLNode * avl_insert(AVLNode * x, int k)
  /*D_requires (avl^(x) & (~ (k i-in keys^(x)))) */
  /*D_ensures ((avl^(ret) & (keys^(ret) s= (old(keys^(x)) union (singleton k)))) & 
         ((height^(ret) i= old(height^(x))) | (height^(ret) i= (old(height^(x)) + 1)))) */
{

	if (x == NULL) {
		AVLNode * leaf = (AVLNode *) malloc(sizeof(AVLNode));
		_(assume leaf != NULL)

		leaf->key = k;

		leaf->height = 0;

		leaf->left = NULL;

		leaf->right = NULL;

		return leaf;
	} else {
    AVLNode * xl = x->left;
    AVLNode * xr = x->right;
		if (k < x->key) {

			AVLNode * new_left = avl_insert(xl, k);

			x->left = new_left;

			return avl_balance(x);
		} else {
			AVLNode * new_right = avl_insert(xr, k);

			x->right = new_right;

			return avl_balance(x);
		}
	}
}
