#include "header.h"
#include <stdio.h>
#include <stdlib.h>

DLNode * dll_delete(DLNode * x, int k)
{
    //pre
  if (x == NULL) {
      //post
    return x;
  } else if (x->key == k) {
    DLNode * tmp = dll_delete(x->next, k);
    free(x);
    //post
    return tmp;
  } else {
    DLNode * tmp = dll_delete(x->next, k);
    x->next = tmp;
    if (tmp) tmp->prev = x;
    //post
    return x;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    DLNode * root = NULL;
    root = create_dll(size);

    root = dll_delete(root, (int)rand());
    return 0;
}
