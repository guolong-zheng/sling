#include "dll.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * node_create(int key){
    DLNode * node = (DLNode *)malloc(sizeof(DLNode));
    node->key = key;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

DLNode * create_dll(int size){
    DLNode * root = NULL:
    for(int i = 0; i < size; i++){
        DLNode * node = node_create((int)rand());
        root = dll_append(root, node);
    }

    return root;
}

DLNode * dll_append(DLNode * x1, DLNode * x2)
{
  if (x1 == NULL) {
    return x2;
  } else {
    DLNode * tmp = dll_append(x1->next, x2);
    x1->next = tmp;
    if (tmp) tmp->prev = x1;
    return x1;
  }
}

DLNode * dll_insert_back(DLNode * x, int k)
{
  if (x == NULL) {
    DLNode * tail = (DLNode *) malloc(sizeof(DLNode));
    tail->key = k;
    tail->next = NULL;
    tail->prev= x;
    return tail;
  } else {
    DLNode * tmp = dll_insert_back(x->next, k);
    x->next = tmp;
    tmp->prev = x;
    return x;
  }
}

void dll_meld(DLNode * u, DLNode * v)
{
  if (v != NULL) {
    v->prev = u;
  }

  if (u != NULL) {
    u->next = v;
  }
}

DLNode * dll_mid_insert(DLNode * u, DLNode * v, int k)
{

  DLNode * r = (DLNode *) malloc(sizeof(DLNode));
  r->key = k;
  r->prev = u;
  r->next = v;
  if (u != NULL) {
    u->next = r;
  }
  if (v != NULL) {
    v->prev = r;
  }
  return r;
}

DLNode * dll_delete(DLNode * x, int k)
{
  if (x == NULL) {
    return x;
  } else if (x->key == k) {
    DLNode * tmp = dll_delete(x->next, k);
    free(x);
    return tmp;
  } else {
    DLNode * tmp = dll_delete(x->next, k);
    x->next = tmp;
    if (tmp) tmp->prev = x;
    return x;
  }
}

DLNode * dll_insert_front(DLNode * x, int k)
{
  if (x == NULL) {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    head->key = k;
    head->next = NULL;
    head->prev = NULL;
    return head;
  } else {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    head->key = k;
    head->next = x;
    x->prev = head;
    return head;
  }
}

DLNode * dll_mid_delete(DLNode * p)
{
  DLNode * v = p->next;
  DLNode * u = p->prev;
  if (v != NULL) {
    v->prev = u;
  }
  if (u != NULL) {
    u->next = v;
  }
  free(p);
}
