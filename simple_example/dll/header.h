#ifndef HEADER_H_
#define HEADER_H_

typedef struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

#define MAX_RAND 1000

DLNode * creat_node();
DLNode * create_dll(int size);

DLNode * dll_append(DLNode * x1, DLNode * x2);
DLNode * dll_insert_back(DLNode * x, int k);
void dll_meld(DLNode * u, DLNode * v);
DLNode * dll_mid_insert(DLNode * u, DLNode * v, int k);
DLNode * dll_delete(DLNode * x, int k);
DLNode * dll_insert_front(DLNode * x, int k);
DLNode * dll_mid_delete(DLNode * p);

#endif
