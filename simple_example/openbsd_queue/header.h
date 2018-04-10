#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  struct node * next;
  struct node * last;
} Node;

Node * create_queue(int size);
Node * create_queue_buggy(int size);

#endif
