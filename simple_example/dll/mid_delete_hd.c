#include "header.h"
#include <stdio.h>
#include <stdlib.h>

DLNode* dll_mid_delete(DLNode* hd, DLNode* p)
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

  if (hd == p) {
    hd = p->next;
  }

  free(p);
  p = NULL;
  //post
  return hd;
}

int main( int argc, char * argv[]){
  int size = 0;
  sscanf(argv[1], "%d", &size);
  DLNode * node1 = create_node();
  DLNode * node2 = create_node();
  DLNode * node3 = create_node();
  DLNode * hd = node1;
  dll_append_node(node1, node2);
  dll_append_node(node1, node3);
  hd = dll_mid_delete(hd, node1);
  return 0;
}
