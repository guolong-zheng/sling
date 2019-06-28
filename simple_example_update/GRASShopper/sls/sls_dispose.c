#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void sls_dispose(Node * lst)
{
  //pre
  while(lst != NULL)
  {
    //loop
    Node * curr = lst;
    lst = lst->next;
    free(curr);
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    sls_dispose(lst);
    sls_dispose(NULL);
    return 0;
}
