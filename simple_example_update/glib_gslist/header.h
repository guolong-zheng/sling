#ifndef HEADER_H_
#define HEADER_H_

#define MAX_RAND 100

typedef struct node {
  int key;
  struct node * next;
} Node;

int rand_num();
Node * create_list(int size);

#endif
