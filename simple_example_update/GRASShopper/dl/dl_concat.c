#include "header.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * dl_concat(DLNode * a, DLNode * b)
{
  //pre
  if (a == NULL) {
    //post
    return b;
  }  else {
    DLNode * curr;
    curr = a;
    while(curr->next != NULL)
    {
       //loop
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

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * a = create_list(size);
    DLNode * b = create_list(size);

    DLNode * res = dl_concat(a, b);
    dl_concat(NULL,NULL);
    dl_concat(NULL,create_list(size));
    dl_concat(create_list(size),NULL);

    return 0;
}
