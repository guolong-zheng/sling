#ifndef REC_H_
#define REC_H_

typedef struct node {
  struct node * next;
} Node;

Node * create_list(int size);

#endif
