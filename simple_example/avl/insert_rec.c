#include "avl.h"
#include <stdlib.h>

AVLNode * avl_insert(AVLNode * x, int k)
{
    //pre
	if (x == NULL) {
		AVLNode * leaf = (AVLNode *) malloc(sizeof(AVLNode));
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
			return avl_balance_node(x);
		} else {
			AVLNode * new_right = avl_insert(xr, k);
			x->right = new_right;
			return avl_balance_node(x);
		}
	}
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    AVLNode * root = create_avl(size);

    AVLNode * res = avl_insert(root, rand_num());
    //post
    return 0;
}
