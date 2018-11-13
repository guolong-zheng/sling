#include "header.h"
#include <stdio.h>
#include <stdlib.h>

DLNode * dll_mid_insert(DLNode * u, DLNode * v, int k)
{
  //pre
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
  //post
  return r;
}

int main( int argc, char * argv[]){
    int size;
    if(argc > 1)
    	sscanf(argv[1], "%d", &size);

    DLNode * hd = create_dll(size);
    DLNode * node = hd->next->next;
    dll_mid_insert(hd->next, node, 4);
    //dll_mid_insert(node, node->next->next, 5);

    return 0;
}
