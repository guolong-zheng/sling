#ifndef CIRCULAR_LIST_H_
#define CIRCULAR_LIST_H_

typedef struct node {
  int key;
  struct node * next;
} CNode;

CNode * create_list(int size);
CNode * lseg_delete_back(CNode * hd, CNode * tl);
CNode * circular_list_delete_back(CNode * x);
CNode * circular_list_delete_front(CNode * x);
CNode * lseg_insert_back(CNode * hd, CNode * tl);
CNode * circular_list_insert_back(CNode * x)
CNode * circular_list_insert_front(CNode * x);

#endif
