#include "header.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * g_list_find(DLNode * list, int data)
{
  //pre
  DLNode * curr = list;
  while(curr != NULL)
  {
    //loop
    if (curr->key == data) {
      break;
    }
    curr = curr->next;
  }
  //post
  return curr;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    DLNode * res = g_list_find(hd, rand_num());

    return 0;
}
