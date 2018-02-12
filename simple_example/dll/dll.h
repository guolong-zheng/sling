#ifndef DLL_H_
#define DLL_H_

typedef struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * node_create(int key);
DLNode * create_dll(int size);
DLNode * dll_append(DLNode * x1, DLNode * x2);
DLNode * dll_insert_back(DLNode * x, int k);
void dll_meld(DLNode * u, DLNode * v);
DLNode * dll_mid_insert(DLNode * u, DLNode * v, int k);
DLNode * dll_delete(DLNode * x, int k);
DLNode * dll_insert_front(DLNode * x, int k);
DLNode * dll_mid_delete(DLNode * p);

#endif
