#include "header.h"
#include <stdlib.h>

void sl_traverse1(Node * lst)
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


void sl_traverse2(Node * lst)
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
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res1 = sl_traverse1(lst);
    Node * res2 = sl_traverse2(lst);
    return 0;
}
