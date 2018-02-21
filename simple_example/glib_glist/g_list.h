#ifndef G_LIST_H_
#define G_LIST_H_

typedef struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * create_list(int size);

#endif
