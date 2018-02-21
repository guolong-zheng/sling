#ifndef OPENBSD_QUEUE_H_
#define OPENBSD_QUEUE_H_

typedef struct node {
  struct node * next;
  struct node * last;
} Node;

Node * create_queue(int size);

#endif
