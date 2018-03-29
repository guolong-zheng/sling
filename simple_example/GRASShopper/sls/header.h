#ifndef SLS_H_
#define SLS_H_

typedef struct node {
   int key;
   struct node * next;
} Node;

Node * create_list(int size);

#endif
