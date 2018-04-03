#include "header.h"
#include <stdio.h>
#include <stdlib.h>

BNode * bst_insert_rec(BNode * x, int k)
{
    //pre
  if (x == NULL) {
    BNode * leaf = (BNode *) malloc(sizeof(BNode));
    leaf->key   = k;
    leaf->left  = NULL;
    leaf->right = NULL;
    //post
    return leaf;
  } else if (k < x->key) {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_rec(l, k);
    x->left = tmp;
    //post
    return x;
  } else {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_rec(r, k);
    x->right = tmp;
    //post
    return x;
  }
}


int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    BNode * res = bst_insert_rec(root, rand_num());

    return 0;
}
