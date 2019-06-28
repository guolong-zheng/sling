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


_(pure) int get_height(AVLNode * x)
	_(reads \universe())
	_(returns x == NULL ? -1 : x->height)
{
	return x == NULL ? -1 : x->height;
}

_(dryad)
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
{

	int lht = get_height(x->left);

	int rht = get_height(x->right);


	AVLNode * right = x->right;
	AVLNode * left  = x->left;

	if (rht == lht + 2) {

		int rlht = get_height(right->left);

		int rrht = get_height(right->right);


		AVLNode * right_left = right->left;
		AVLNode * right_right = right->right;


		if (rlht <= rrht) {
      int inc_rlht = rlht + 1;
			x->height = inc_rlht;

			x->right = right_left;
			
      int inc_inc_rlht = rlht + 2;
			right->height = inc_inc_rlht;

			right->left = x;

			return right;

		} else {
			AVLNode * right_left_left = right_left->left;

			AVLNode * right_left_right = right_left->right;

      int inc_lht = lht + 1;
			x->height = inc_lht;

			x->right = right_left_left;
			
      int inc_rrht = rrht + 1;
			right->height = inc_rrht;

			right->left = right_left_right;
			
      int inc_inc_lht = lht + 2;
			right_left->height = inc_inc_lht;

			right_left->left = x;

			right_left->right = right;

			return right_left;

		}
	} else if (lht == rht + 2) {

		int llht = get_height(left->left);

		int lrht = get_height(left->right);


		AVLNode * left_left = left->left;
		AVLNode * left_right = left->right;

		if (lrht <= llht) {
      int inc_lrht = lrht + 1;
			x->height = inc_lrht;

			x->left = left_right;

      int inc_inc_lrht = lrht + 2;
			left->height = inc_inc_lrht;

			left->right = x;

			return left;
		} else { // lrht > llht
			// rotate-left |> rotate-right
			AVLNode * left_right_left = left_right->left;

			AVLNode * left_right_right = left_right->right;

      int inc_rht = rht + 1;
			x->height = inc_rht;

			x->left   = left_right_right;

      int inc_llht = llht + 1;
			left->height = inc_llht;

			left->right = left_right_left;

      int inc_inc_rht = rht + 2;
			left_right->height = inc_inc_rht;

			left_right->left = left;

			left_right->right = x;

			return left_right;
		}
	} else if (rht == lht + 1) {
  
    int inc_rht = rht + 1;
		x->height = inc_rht;

		return x;
	} else {
		
    int inc_lht = lht + 1;
		x->height = inc_lht;

		return x;
	
	}
}
