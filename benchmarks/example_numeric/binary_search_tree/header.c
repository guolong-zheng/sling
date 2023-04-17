#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

BNode * create_tree(int size)
{
    BNode * root = NULL;
    int key;
    srand(time(0));
    int nums[] = {50, 24, 13, 30, 70, 80, 40, 25, 56, 62};
    for(int i = 0; i < size; i++){
        //key = rand_num();
        key = nums[i];
        //printf("%d\n", key);
        root = bst_insert_node(root, key);
    }
    return root;
}

BNode * bst_insert_node(BNode * x, int k)
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
    BNode * tmp = bst_insert_node(l, k);
    x->left = tmp;
    return x;
  } else {
    BNode * l = x->left;
    BNode * r = x->right;
    BNode * tmp = bst_insert_node(r, k);
    x->right = tmp;
    return x;
  }
}
