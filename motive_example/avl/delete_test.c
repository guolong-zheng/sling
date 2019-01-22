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
    root = avl_delete(root, 1);
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

AVLNode * avl_delete(AVLNode * root, int key)
{
        //pres
	if (root == NULL) {
		return root;
	} 
        AVLNode * origLeft = root->left;
	AVLNode * origRight = root->right;

        if (key < root -> key)
            root->left = avl_delete(root->left,key);
            //root->left = avl_delete(left,key);
        else if(key > root->key)
            root->right = avl_delete(root->right, key);
            //root->right = avl_delete(right,key);
        else{
            /*
            if( (left == NULL) || (right == NULL) ){
                AVLNode * tmp = left ? left : right;
                if(tmp == NULL){
	            tmp = root;
                    root = NULL;
		}else
		    *root = *tmp;
                  
                free(tmp); 
                //if(tmp != NULL)
                   // printf("adlfalfalfjak\n");
            }
            else{
                int succ = avl_find_smallest(right);
                root->key = succ;
                root->right = avl_delete(right, succ);
            }
            */
            
            if( (root->left == NULL) || (root->right == NULL) ){
                AVLNode * tmp = root->left ? root->left : root->right;
                if(tmp == NULL){
	            tmp = root;
                    return root;
		}else
		    *root = *tmp;
                free(tmp); 
               
            }
            else{
                int succ = avl_find_smallest(root->right);
                root->key = succ;
                root->right = avl_delete(root->right, succ);
                
            }
            
        }
        AVLNode * newTree = avl_balance_node(root);        
        //post
        return newTree;
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
