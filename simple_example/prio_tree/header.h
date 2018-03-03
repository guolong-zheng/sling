#ifndef HEADER_H_
#define HEADER_H_

typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
  int prio;
} BNode;

#define MAX_RAND 2000

int rand_num();
BNode * create_tree(int size);
BNode * treap_delete_rec(BNode * x, int k);
int treap_find_rec(BNode * x, int k);
BNode * treap_insert_rec(BNode * x, int k, int p);
BNode * treap_remove_root_rec(BNode * x);


#endif
