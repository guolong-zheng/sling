#ifndef HEADER_H_
#define HEADER_H_

#define MAX_RAND 100

typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

int rand_num();
BNode * create_tree(int size);
BNode * bst_insert_node(BNode * x, int k);

#endif
