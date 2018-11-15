
#include <stdlib.h>

typedef
/*D_tag a_node */
struct a_node {
  struct a_node * left;
  struct a_node * right;
  int key;
  int height;
} AVLNode;

int avl_find_smallest(AVLNode * x);

AVLNode * avl_balance(AVLNode * x);

AVLNode * avl_delete(AVLNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	if (x == NULL) {
		return x;
	} else {
	  AVLNode * right = x->right;
    AVLNode * left = x->left;
		if (x->key == k) {
			if (left == NULL && right == NULL) {
				free(x);
				return NULL;
			} else if (left  == NULL) {
				free(x);
				return right;
			} else if (right == NULL) {
				free(x);
				return left;
			} else {
				int succ = avl_find_smallest(right);

				AVLNode * new_right = avl_delete(right, succ);

				x->key = succ;

				x->right = new_right;

				return avl_balance(x);
			}
		} else if (x->key > k) {
			AVLNode * new_left = avl_delete(left, k);

			x->left = new_left;

			return avl_balance(x);

		} else {// x->key < k

			AVLNode * new_right = avl_delete(right, k);

			x->right = new_right;

			return avl_balance(x);
		}

	}
}
