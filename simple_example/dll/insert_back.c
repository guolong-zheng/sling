#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

DLNode * dll_insert_back(DLNode * x, int k)
{
    //pre
  if (x == NULL) {
    DLNode * tail = (DLNode *) malloc(sizeof(DLNode));
    tail->key = k;
    tail->next = NULL;
    tail->prev= x;
    //post
    return tail;
  } else {
    DLNode * tmp = dll_insert_back(x->next, k);
    x->next = tmp;
    tmp->prev = x;
    //post
    return x;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    DLNode * root = NULL;
    root = create_dll(size);

    DLNode * res = NULL;
    res = dll_insert_back(root, rand_num());

    return 0;
}
