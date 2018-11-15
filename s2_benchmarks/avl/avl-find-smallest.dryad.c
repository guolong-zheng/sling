
#include <stdlib.h>

typedef
/*D_tag a_node */
struct a_node {
  struct a_node * left;
  struct a_node * right;
  int key;
  int height;
} AVLNode;

int avl_find_smallest(AVLNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		return r;
	}
}

