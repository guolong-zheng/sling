#define MAX_RAND 1000

typedef struct t_node {
  struct t_node * left;
  struct t_node * right;
  int key;
} TNode;

int rand_num();
TNode * crate_node();
TNode * create_tree(int size);
TNode * insert(TNode * root, TNode * node);
