#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void sls_traverse1(Node * lst)
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

void sls_traverse2(Node * lst)
{
  //pre
  Node * curr;
  if (lst != NULL) {
    curr = lst;
    while(curr != NULL)
    {
      //loop
      curr = curr->next;
    }
  }
  //post
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    sls_traverse1(lst);
    sls_traverse1(NULL);
    //sls_traverse2(lst);
    return 0;
}
