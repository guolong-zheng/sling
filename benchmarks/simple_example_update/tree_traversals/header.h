#define MAX_RAND 100

typedef struct t_node {
  struct t_node * left;
  struct t_node * right;
  int key;
} TNode;

int rand_num();
TNode * create_tree(int size);
TNode * insert(TNode * root, TNode * node);
