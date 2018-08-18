#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int avl_find_smallest(AVLNode * x);
AVLNode * avl_delete(AVLNode * x, int k);

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    AVLNode * root = create_avl(size);

    AVLNode * res = avl_delete(root, rand_num());
    avl_delete(NULL, rand_num());
    avl_delete(NULL, -100);
    avl_delete(NULL, 100);
    return 0;
}

AVLNode * avl_delete(AVLNode * x, int k)
{
    //pre
	if (x == NULL) {
        //post
		return x;
	} else {
	    AVLNode * right = x->right;
        AVLNode * left = x->left;
		if (x->key == k) {
			if (left == NULL && right == NULL) {
				free(x);
                //post
				return NULL;
			} else if (left  == NULL) {
				free(x);
                //post
				return right;
			} else if (right == NULL) {
				free(x);
                //post
				return left;
			} else {
				int succ = avl_find_smallest(right);
				AVLNode * new_right = avl_delete(right, succ);
				x->key = succ;
				x->right = new_right;
                //post
				return avl_balance_node(x);
			}
		} else if (x->key > k) {
			AVLNode * new_left = avl_delete(left, k);
			x->left = new_left;
            //post
			return avl_balance_node(x);
		} else {
			AVLNode * new_right = avl_delete(right, k);
			x->right = new_right;
            //post
			return avl_balance_node(x);
		}

	}
}

int avl_find_smallest(AVLNode * x)
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		return r;
	}
}
