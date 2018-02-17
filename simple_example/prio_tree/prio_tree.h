#ifndef PRIO_TREE_H_
#define PRIO_TREE_H_

typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
  int prio;
} BNode;

BNode * create_tree(int size);
BNode * treap_delete_rec(BNode * x, int k);
int treap_find_rec(BNode * x, int k);
BNode * treap_insert_rec(BNode * x, int k, int p);
BNode * treap_remove_root_rec(BNode * x);


#endif
