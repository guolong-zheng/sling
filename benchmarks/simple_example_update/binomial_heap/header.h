#define MAX_RAND 100

typedef struct node {
  int key;
  int order;
  struct node * children;
  struct node * sibling;
} SNnode;

int rand_num();
SNnode * create_heap(int size);
int binomial_heap_find__minimum_rec(SNnode * x);
SNnode * binomial_heap_merge_rec(SNnode * x, SNnode * y);
