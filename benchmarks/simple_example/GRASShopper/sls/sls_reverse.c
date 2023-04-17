#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sls_reverse(Node * lst)
{
  //pre
  Node * curr = lst;
  Node * rev = NULL;
  Node * tmp = NULL;
  while(curr != NULL)
  {
    //loop
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    rev = tmp;
  }
  //post
  return rev;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    Node * res = sls_reverse(lst);
    return 0;
}
