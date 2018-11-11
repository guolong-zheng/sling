#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  struct node * next;
} Node;

Node * create_list(int size);

void free_list(Node * root);
#endif
