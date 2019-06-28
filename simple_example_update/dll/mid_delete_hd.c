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
  DLNode * hd = create_dll(size);
  DLNode * node = hd->next->next->next;
  hd = dll_mid_delete(hd, node);
  return 0;
}
