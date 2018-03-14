#include "header.h"
#include <stdio.h>
#include <stdlib.h>

DLNode * dll_mid_delete(DLNode * p)
{
  //pre
  DLNode * v = p->next;
  DLNode * u = p->prev;
  if (v != NULL) {
    v->prev = u;
  }
  if (u != NULL) {
    u->next = v;
  }
  free(p);
  //post
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    DLNode * node1 = node_create(1);
    DLNode * node2 = node_create(2);
    DLNode * node3 = node_create(3);

    dll_append_node(node1, node2);
    dll_append_node(node1, node3);

    dll_mid_delete(node2);
    return 0;
}
