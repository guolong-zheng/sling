#include "header.h"

BNode * bst_remove_root_rec(BNode * x)
{
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
    BNode * left = x->left;
    BNode * right_left = right->left;
    BNode * right_right = right->right;
    x->right = right_left;
    BNode * tmp = bst_remove_root_rec(x);
    right->left = tmp;
    //post
    return right;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    BNode * res = bst_remove_root_rec(root);

    return 0;
}
