#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void dl_traverse(DLNode * lst)
{
  //pre
  DLNode * curr = lst;
  while(curr != NULL)
  {
    //loop
    curr = curr->next;
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    dl_traverse(lst);
    dl_traverse(NULL);
    return 0;
}
