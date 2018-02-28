#ifndef SLL_H_
#define SLL_H_

#define MAX_RAND 1000

typedef struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * create_node();
SNnode * create_sll(int size);
SNnode * sll_append(SNnode * x1, SNnode * x2);

#endif
