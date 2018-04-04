typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
  int prio;
} BNode;

#define MAX_RAND 100

int rand_num();
BNode * create_tree(int size);
BNode * treap_insert_node(BNode * x, int k, int p);
