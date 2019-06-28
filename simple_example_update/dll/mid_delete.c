#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void dll_mid_delete(DLNode * p)
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
    DLNode * hd = create_dll(size);
    DLNode * node = hd->next->next;
    dll_mid_delete(node);
    return 0;
}
