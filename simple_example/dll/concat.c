#include "header.h"
#include <stdio.h>

DLNode* dll_concat(DLNode* a, DLNode* b)
{
  //pre
  if (a == NULL) {
    //post
    return b;
  } else {
    DLNode* curr = a;
    while (curr->next != NULL)
      //inv
    {
      curr = curr->next;
    }

    curr->next = b;
    if (b != NULL) {
      b->prev = curr;
    }

    //post
    return a;
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
  return 0;
}
