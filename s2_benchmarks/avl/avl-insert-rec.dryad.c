
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


AVLNode * avl_insert(AVLNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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
