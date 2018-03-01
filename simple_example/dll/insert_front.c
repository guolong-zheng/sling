#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

DLNode * dll_insert_front(DLNode * x, int k)
{
    //pre
  if (x == NULL) {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    head->key = k;
    head->next = NULL;
    head->prev = NULL;
    //post
    return head;
  } else {
    DLNode * head = (DLNode *) malloc(sizeof(DLNode));
    head->key = k;
    head->next = x;
    x->prev = head;
    //post
    return head;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    DLNode * root = NULL;
    root = create_dll(size);

    DLNode * res = NULL;
    res = dll_insert_front(root, rand_num());
    return 0;
}
