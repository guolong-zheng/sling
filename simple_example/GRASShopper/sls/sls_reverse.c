#include "header.h"
#include <stdlib.h>

Node * sls_reverse(Node * lst)
{
  //pre
  Node * curr = lst;
  Node * rev = NULL;
  while(curr != NULL)
  {
    //loop
    Node * tmp;
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    rev = tmp;
  }
  //post
  return rev;
}

int main(int argc, char * argv){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    Node * res = sls_reverse(lst);
    return 0;
}
