#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int avl_find_smallest(AVLNode * x);
AVLNode * avl_delete(AVLNode * x, int k);
void inorder(AVLNode* x);
void nullptr(AVLNode** x);

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    AVLNode * root = NULL;
    root = avl_insert_node(root, 9);
    root = avl_insert_node(root, 5);
    root = avl_insert_node(root, 10);
    root = avl_insert_node(root, 0);
    root = avl_insert_node(root, 6);
    root = avl_insert_node(root, 11);
    root = avl_insert_node(root, -1);
    root = avl_insert_node(root, 1);
    root = avl_insert_node(root, 2);

    //AVLNode * tmp = root;
    //inorder(tmp);

    //root = avl_delete(root, -100);
    //root = avl_delete(root, 100);
    //root = avl_delete(root, 11);
    root = avl_delete(root, 10);
    root = avl_delete(root, 5);
    //tmp = root;
    //inorder(tmp);
    //root = avl_delete(root, 10);

    return 0;
}

void nullptr(AVLNode ** x){
    *x = NULL;
    return;
}

void inorder(AVLNode * x){
   if(x == NULL)
        return;
   printf("%d ", x->key);
   inorder(x->left);
   printf("\n");
   inorder(x->right); 
}

AVLNode * avl_delete(AVLNode * x, int k)
{
//pre

	if (x == NULL) {
		return x;
	} else {
	    AVLNode * oldRight = x->right;
            AVLNode * oldLeft = x->left;
		if (x->key == k) {
			if (x->left == NULL && x->right == NULL) {
				free(x);
				return NULL;
			} else if (x->left  == NULL) {
				free(x);
				return x->right;
			} else if (x->right == NULL) {
				free(x);
				return x->left;
			} else {
				int succ = avl_find_smallest(x->right);
				AVLNode * newRight = avl_delete(x->right, succ);
				x->key = succ;
				x->right = newRight;
                                AVLNode * res = avl_balance_node(x);
				return res;
			}
		} else if (x->key > k) {
			AVLNode * newLeft = avl_delete(x->left, k);
			x->left = newLeft;
                        AVLNode * res = NULL; 
                        res = avl_balance_node(x);
			return res;
		} else {
			AVLNode * newRight = avl_delete(x->right, k);
			x->right = newRight;
                        AVLNode * m = avl_balance_node(x);
                        //post
			return m;
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
