#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  struct node * next;
  struct node * last;
} Node;

Node * create_queue(int size);

#endif
