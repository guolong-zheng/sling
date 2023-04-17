#ifndef HEADER_H_
#define HEADER_H_

#define MAX_RAND 100

typedef struct node {
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * create_list(int size);

#endif
