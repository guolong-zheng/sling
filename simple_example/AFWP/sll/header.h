#define MAX_RAND 100

typedef struct node {
  struct node * next;
} NNode;

typedef struct KNode {
   int key;
   struct KNode * next;
} KNode;

NNode * create_list(int size);
