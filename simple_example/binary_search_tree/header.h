#ifndef HEADER_H_
#define HEADER_H_

#define MAX_RAND 2000

typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

int rand_num();
BNode * create_tree(int size);

BNode * bst_remove_root(BNode * x);
BNode * find_smallest(BNode * x);
BNode * bst_delete_rec(BNode * x, int k);
int bst_find_rec(BNode * x, int k);
BNode * bst_insert_rec(BNode * x, int k);
BNode * bst_remove_root_rec(BNode * x);
BNode * bst_find_iter(BNode * x, int k);

#endif
