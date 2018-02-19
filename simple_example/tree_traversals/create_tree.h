typedef struct t_node {
  struct t_node * left;
  struct t_node * right;
  int key;
} TNode;

TNode * insert(TNode * root, int key);
TNode * create_tree(int size);
