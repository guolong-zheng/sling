typedef struct node {
  struct node * next;
  struct node * prev;
} DLNode;

typedef struct snode{
    struct snode * next;
} Node;

Node * create_sll(int size);
DLNode * create_dll(int size);
