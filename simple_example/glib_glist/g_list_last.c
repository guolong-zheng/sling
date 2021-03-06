#include "header.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * g_list_last(DLNode * list)
{
  //pre
  DLNode * curr = list;
  if (curr != NULL) {
    while(curr->next != NULL)
    {
      //loop
      curr = curr->next;
    }
  }
  //post
  return curr;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    DLNode * res = g_list_last(hd);

    return 0;
}
