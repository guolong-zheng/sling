#ifndef SLL_H_
#define SLL_H_

typedef struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * node_create(int key);
SNnode * create_sll(int size);
SNnode * sll_append(SNnode * x1, SNnode * x2);
SNnode * sll_delete_all(SNnode * x, int k);
SNnode * sll_insert_back(SNnode * x, int k);
SNnode * sll_insert(SNnode * x, int k);
SNnode * sll_copy(SNnode * x, int k);
int sll_find(SNnode * x, int k);
SNnode * sll_insert_front(SNnode * x, int k);
SNnode * sll_reverse(SNnode * x);

#endif
