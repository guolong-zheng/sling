#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
   int key;
   struct node * next;
} Node;

Node * create_list(int init, int size);
Node * create_random(int size);

#endif
