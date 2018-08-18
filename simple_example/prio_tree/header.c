#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int rand_num(){
    return rand()%(2*MAX_RAND+1) - MAX_RAND;
}

BNode * create_tree(int size){
    BNode * root = NULL;
    for(int i = 0; i < size; i++){
        int k = rand_num();
        int p = rand_num();
        printf("%d   %d\n", k, p);
        root = treap_insert_node(root, k, p);
    }
    return root;
}

BNode * treap_insert_node(BNode * x, int k, int p)
{
  if (x == NULL) {
    BNode * leaf = (BNode *) malloc(sizeof(BNode));
    leaf->key = k;
    leaf->prio = p;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
  } else {
    if (k < x->key) {
      BNode * xr = x->right;
      BNode * xl = x->left;
      BNode * tmp = treap_insert_node(xl, k, p);
      if (tmp->prio <= x->prio) {
        x->left = tmp;
        return x;
      } else {
        BNode * lr = tmp->right;
        x->left = lr;
        tmp->right = x;
        return tmp;
      }
    } else {
      BNode * xr = x->right;
      BNode * xl = x->left;
      BNode * tmp = treap_insert_node(xr, k, p);
      if (tmp->prio <= x->prio) {
        x->right = tmp;
        return x;
      } else {
        BNode * rl = tmp->left;
        x->right = rl;
        tmp->left = x;
        return tmp;
      }
    }
  }
}
