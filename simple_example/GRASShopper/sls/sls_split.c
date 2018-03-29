#include "header.h"
#include <stdlib.h>

Node * split(Node * x)
{
  //pre
  Node * z = x;

  Node * curr = x;
  while(curr != NULL)
  {
      //loop
    z = z->next;
    curr = curr->next;
    if (curr != NULL) {
      curr = curr->next;
    }
  }
  if (z != NULL) {
    Node * tmp = z;
    z = z->next;
    tmp->next = NULL;
  }
  //post
  return z;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    Node * res = split(lst);
    return 0;
}
