#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

#define MAX_RAND 1000

int rand_num();
DLNode * create_node();
DLNode * create_dll(int size);
DLNode * dll_append_node(DLNode * x1, DLNode * x2);

#endif
