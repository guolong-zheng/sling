#include "header.h"
#include <stdlib.h>
#include <stdio.h>

BNode * treap_insert_rec(BNode * x, int k, int p)
{
  //pre
  if (x == NULL) {
    BNode * leaf = (BNode *) malloc(sizeof(BNode));
    leaf->key = k;
    leaf->prio = p;
    leaf->left = NULL;
    leaf->right = NULL;
    //post
    return leaf;
  } else {
    if (k < x->key) {
      BNode * xr = x->right;
      BNode * xl = x->left;
      BNode * tmp = treap_insert_rec(xl, k, p);
      if (tmp->prio <= x->prio) {
        x->left = tmp;
        //post
        return x;
      } else {
        BNode * lr = tmp->right;
        x->left = lr;
        tmp->right = x;
        //post
        return tmp;
      }
    } else {
      BNode * xr = x->right;
      BNode * xl = x->left;
      BNode * tmp = treap_insert_rec(xr, k, p);
      if (tmp->prio <= x->prio) {
        x->right = tmp;
        //post
        return x;
      } else {
        BNode * rl = tmp->left;
        x->right = rl;
        tmp->left = x;
        //post
        return tmp;
      }
    }
  }
}

int main( int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);
    BNode * res = treap_insert_rec(root, rand_num(),rand_num());
    treap_insert_rec(root, -100,rand_num());
    treap_insert_rec(root, 100,rand_num());
    return 0;
}
