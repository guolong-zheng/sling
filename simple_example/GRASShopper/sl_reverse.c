#include "sl.h"
#include <stdlib.h>

Node * sl_reverse(Node * lst)
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

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res = sl_reverse(lst);
    return 0;
}
