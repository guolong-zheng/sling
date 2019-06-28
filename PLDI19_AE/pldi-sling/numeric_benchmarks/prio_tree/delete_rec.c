#include "header.h"
#include <stdlib.h>
#include <stdio.h>

BNode * treap_remove_root_rec(BNode * x);

BNode * treap_delete_rec(BNode * x, int k)
{
   //pre
   if(x==NULL)
     //post
    return x;
  if(x->key == k) {
    BNode * r = treap_remove_root_rec(x);
    //post
    return r;
  } else if (k < x->key) {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = treap_delete_rec(xl, k);
    x->left = l;
    //post
    return x;
  } else {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = treap_delete_rec(xr, k);
    x->right = r;
    //post
    return x;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    BNode * root = create_tree(size);
    BNode * res = treap_delete_rec(root, rand_num());

    return 0;
}


BNode * treap_remove_root_rec(BNode * x)
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
    BNode * left  = x->left;
    if(left->prio <= right->prio) {
      BNode * right_left = right->left;
      BNode * right_right = right->right;
      BNode * left_left = left->left;
      BNode * left_right = left->right;
      x->right = right_left;
      BNode * tmp = treap_remove_root_rec(x);
      right->left = tmp;
      return right;
    } else {
      BNode * right_left = right->left;
      BNode * right_right = right->right;
      BNode * left_left = left->left;
      BNode * left_right = left->right;
      x->left = left_right;
      BNode * tmp = treap_remove_root_rec(x);
      left->right = tmp;
      return left;
    }
  }
}
