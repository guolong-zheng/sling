#include "prio_tree.h"
#include <stdio.h>
#include <stdlib.h>

BNode * create_tree(int size){
    BNode * root = NULL;
    for(int i = 0; i < size; i++){
        root = treap_insert_rec(root, (int)rand(), (int)rand());
    }

    return root;
}

BNode * treap_delete_rec(BNode * x, int k)
{
  if(x->key == k) {
    BNode * r = treap_remove_root_rec(x);
    return r;
  } else if (k < x->key) {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = treap_delete_rec(xl, k);
    x->left = l;
    return x;
  } else {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = treap_delete_rec(xr, k);
    x->right = r;
    return x;
  }
}

int treap_find_rec(BNode * x, int k)
{
  if (x == NULL) {
    return 0;
  } else {
      if (k == x->key) {
        return 1;
      } else if (k < x->key) {
        int r = treap_find_rec(x->left, k);
        return r;
      } else {
        int r = treap_find_rec(x->right, k);
        return r;
    }
  }
}

BNode * treap_insert_rec(BNode * x, int k, int p)
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
      BNode * tmp = treap_insert_rec(xl, k, p);
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
      BNode * tmp = treap_insert_rec(xr, k, p);
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
