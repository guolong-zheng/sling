#include "avl.h"
#include <stdlib.h>

AVLNode * create_avl(int size){
    AVLNode * root = NULL;
    for(int i = 0; i < size; i++){
        root = avl_insert(root, (int)rand());
    }
    return root;
}

int get_height(AVLNode * x)
{
	return x == NULL ? -1 : x->height;
}

AVLNode * avl_balance(AVLNode * x)
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
		} else {
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

int avl_find_smallest(AVLNode * x)
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		return r;
	}
}


AVLNode * avl_delete(AVLNode * x, int k)
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

AVLNode * avl_insert(AVLNode * x, int k)
{
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
			return avl_balance(x);
		} else {
			AVLNode * new_right = avl_insert(xr, k);
			x->right = new_right;
			return avl_balance(x);
		}
	}
}
