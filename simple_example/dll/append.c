#include "header.h"
#include <stdio.h>

DLNode * dll_append(DLNode * x1, DLNode * x2)
{
  //pre
  if (x1 == NULL) {
    //post
    return x2;
  } else {
    DLNode * tmp = dll_append(x1->next, x2);
    x1->next = tmp;
    if (tmp) tmp->prev = x1;
    //post
    return x1;
  }
}

int main( int argc, char * argv[]) {
    int size = 5;
    if (argc > 1)
    	sscanf(argv[1], "%d", &size);

    DLNode * root = NULL;
    root = create_dll(size);

    DLNode * node = create_dll(size);
    DLNode * res = NULL;
    res = dll_append(root, node);
    return 0;
}
