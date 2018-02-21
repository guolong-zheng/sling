#ifndef DL_H_
#define DL_H_

typedef struct node {
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * create_list(int size);

#endif
