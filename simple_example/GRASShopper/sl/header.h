#ifndef SL_H_
#define SL_H_

typedef struct node {
  struct node * next;
} Node;

Node * create_list(int size);

#endif
