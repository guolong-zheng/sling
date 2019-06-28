#include "header.h"
#include <stdlib.h>
#include <stdio.h>

BNode * bst_remove_root(BNode * x);
BNode * bst_delete_rec(BNode * x, int k);

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    BNode * res = bst_delete_rec(root, rand_num());
    bst_delete_rec(NULL, rand_num());
    return 0;
}

BNode * bst_delete_rec(BNode * x, int k)
{
  //pre
  if (x == NULL) {
    //post
    return x;
  } else if (x->key == k) {
    BNode * r = bst_remove_root(x);
    //post
    return r;
  } else if (k < x->key) {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = bst_delete_rec(xl, k);
    // BNode * l = bst_delete_rec(x->left, k);
    x->left = l;
    //post
    return x;
  } else {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = bst_delete_rec(xr, k);
    // BNode * r = bst_delete_rec(x->right, k);
    x->right = r;
    //post
    return x;
  }
}

BNode * bst_remove_root(BNode * x)
{
  if(x->left == NULL && x->right == NULL) {
    free(x);
    return NULL;
  } else if (x->left == NULL) {
    BNode * right = x->right;
    free(x);
    return right;
  } else if (x->right == NULL) {
    BNode * left = x->left;
    free(x);
    return left;
  } else {
    BNode * right = x->right;
    BNode * left = x->left;
    BNode * right_left = right->left;
    BNode * right_right = right->right;
    x->right = right_left;
    BNode * tmp = bst_remove_root(x);
    right->left = tmp;
    return right;
  }
}
