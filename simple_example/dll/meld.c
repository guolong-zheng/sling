#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

void dll_meld(DLNode * u, DLNode * v)
{
  //pre
  if (v != NULL) {
    v->prev = u;
  }

  if (u != NULL) {
    u->next = v;
  }
  //post
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    DLNode * root1 = create_dll(size);
    DLNode * root2 = create_dll(size);

    dll_meld(root1, root2);

    return 0;
}
