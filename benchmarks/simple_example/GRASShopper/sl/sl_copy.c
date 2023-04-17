#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sl_copy(Node * lst)
{
  //pre
  Node * curr = lst;
  Node * cp = NULL;
  Node * old_cp = NULL;
  while(curr != NULL)
  {
    //loop
    old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    cp->next = old_cp;
    curr = curr->next;
  }
  //post
  return cp;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    Node * lst = create_list(size);
    Node * res = sl_copy(lst);
    return 0;
}
