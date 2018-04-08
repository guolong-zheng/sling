#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

#define MAX_RAND 100

int rand_num();
DLNode * create_list(int size);

#endif
