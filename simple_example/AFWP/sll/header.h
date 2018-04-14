#define MAX_RAND 100

typedef struct node {
  struct node * next;
} Node;

typedef struct KNode {
   int key;
   struct KNode * next;
} KNode;

Node * create_list(int size);
