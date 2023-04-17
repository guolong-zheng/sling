#include "header.h"
#include <stdlib.h>
#include <stdio.h>

BNode * treap_remove_root_rec(BNode * x)
{
    if(x==NULL)
        return NULL;
    //pre
  if(x->left == NULL && x->right == NULL) {
    free(x);
    //post
    return NULL;
  } else if (x->left == NULL) {
    BNode * right = x->right;
    free(x);
    //post
    return right;
  } else if (x->right == NULL) {
    BNode * left = x->left;
    free(x);
    //post
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
      //post
      return right;
    } else {
      BNode * right_left = right->left;
      BNode * right_right = right->right;
      BNode * left_left = left->left;
      BNode * left_right = left->right;
      x->left = left_right;
      BNode * tmp = treap_remove_root_rec(x);
      left->right = tmp;
      //post
      return left;
    }
  }
}

int main( int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    BNode * res = treap_remove_root_rec(root);
    return 0;
}
