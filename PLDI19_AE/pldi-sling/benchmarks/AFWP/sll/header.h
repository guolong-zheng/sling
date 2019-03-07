#define MAX_RAND 10

typedef struct node {
  struct node * next;
} Node;

typedef struct knode {
   int key;
   struct knode * next;
} KNode;

int rand_num();
Node * create_list(int size);
KNode * create_klist(int size);
