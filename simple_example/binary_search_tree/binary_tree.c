#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

BNode * create_tree(int size)
{
    BNode * root = NULL;
    int key;
    for(int i = 0; i < size; i++){
        key = (int)rand();
        root = bst_insert_rec(key);
    }

    return root;
}

BNode * bst_remove_root(BNode * x)
{
    if(x->left== NULL && x->right == NULL){
        free(x);
        return NULL;
    }else if(x->left == NULL){
        BNnode * res = x->right;
        free(x);
        return res;
    }else if(x->right == NULL){
        BNnode * res = x->left;
        free(x);
        return res;
    }else{
        BNode * tmp = find_smallest(x->right);
        x->key = tmp->key;
        bst_remove_root(tmp);
    }
}

BNode * find_smallest(BNode * x)
{
    while(x->left != NULL)
    {
        x = x->left;
    }

    return x;
}

BNode * bst_delete_rec(BNode * x, int k)
{
  if(x->key == k) {
    BNode * r = bst_remove_root(x);
    return r;
  } else if (k < x->key) {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = bst_delete_rec(xl, k);
    x->left = l;
    return x;
  } else {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = bst_delete_rec(xr, k);
    x->right = r;
    return x;
  }
}

int bst_find_rec(BNode * x, int k)
{
  if (x == NULL) {
    return 0;
  } else {
      if (k == x->key) {
        return 1;
      } else if (k < x->key) {
        int r = bst_find_rec(x->left, k);
        return r;
      } else {
        int r = bst_find_rec(x->right, k);
        return r;
    }
  }
}

BNode * bst_insert_rec(BNode * x, int k)
{

  if (x == NULL) {
    BNode * leaf = (BNode *) malloc(sizeof(BNode));
    leaf->key   = k;
    leaf->left  = NULL;
    leaf->right = NULL;
    return leaf;
  } else if (k < x->key) {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_rec(l, k);
    x->left = tmp;
    return x;
  } else {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_rec(r, k);
    x->right = tmp;
    return x;
  }
}

BNode * bst_remove_root_rec(BNode * x)
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
    BNode * tmp = bst_remove_root_rec(x);
    right->left = tmp;
    return right;
  }
}

BNode * bst_find_iter(BNode * x, int k)
{
  BNode * curr = x;
  while(curr != NULL)
  {
    if (curr->key == k) {
      return curr;
    } else if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  return curr;
}
