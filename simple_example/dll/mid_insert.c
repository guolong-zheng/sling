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
    int size;
    if(argc > 1)
    	sscanf(argv[1], "%d", &size);

    DLNode * node1 = create_node();
    DLNode * node2 = create_node();
    DLNode * node3 = create_node();

    DLNode * root = dll_append_node(node1, node2);
    root = dll_append_node(root, node3);

    root = dll_mid_insert(node1, node2, 4);

    return 0;
}
