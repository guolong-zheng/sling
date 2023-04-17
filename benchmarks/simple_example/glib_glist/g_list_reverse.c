#include "header.h"
#include <stdio.h>
#include <stdlib.h>

DLNode * g_list_reverse(DLNode * list)
{
  //pre
  DLNode * last = NULL;
  DLNode * curr = list;
  DLNode * last_prev = NULL;
  while(curr != NULL)
  {
    //loop
    last = curr;
    curr = curr->next;
    last_prev = last->prev;
    last->next = last_prev;
    last->prev = curr;
  }
  //post
  return last;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    DLNode * res = g_list_reverse(hd);

    return 0;
}
