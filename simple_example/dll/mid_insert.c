#include "header.h"
#include <stdio.h>
#include <stdlib.h>

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

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    DLNode * node1 = node_create(1);
    DLNode * node2 = node_create(2);
    DLNode * node3 = node_create(3);

    DLNode * root = dll_append(node1, node2);
    root = dll_append(root, node3);

    root = dll_mid_insert(node1, node2, 4);

    return 0;
}
