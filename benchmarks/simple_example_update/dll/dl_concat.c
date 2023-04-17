#include "header.h"
#include <stdio.h>

DLNode* dll_concat(DLNode* x, DLNode* y)
{
  //pre
  if (x == NULL) {
    //post
    return y;
  } else {
    DLNode *tmp = dll_concat(x->next, y);
    x->next = tmp;
    if (tmp) tmp->prev = x;
    //post
    return x;
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
  res = dll_concat(root, node);
  dll_concat(NULL, NULL);
  dll_concat(create_dll(size),NULL);
  dll_concat(NULL, create_dll(size));
  return 0;
}
