#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  int key;
  struct node * next;
} CNode;

#define MAX_RAND 2000

int rand_num();
CNode * create_list(int size);

#endif
