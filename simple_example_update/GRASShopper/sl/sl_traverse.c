#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void sl_traverse(Node * lst)
{
  //pre
  Node * curr = lst;
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
    Node * lst = create_list(size);
    sl_traverse(lst);
    sl_traverse(NULL);
    return 0;
}
