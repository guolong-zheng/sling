#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sls_remove(Node * lst, int value)
{
  //pre
  Node * curr = lst;
  Node * prv = NULL;
  while(curr != NULL && curr->key < value)
  {
    //loop
    prv = curr;
    curr = curr->next;
  }

  if (curr != NULL && curr->key == value)
  {
    if (prv == NULL) {
      lst = curr->next;
    }  else {
      Node * curr_next = curr->next;
      prv->next = curr_next;
    }
    free(curr);
  }
  //post
  return lst;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * lst =create_list(1, size);
    sls_remove(lst, 100);
    sls_remove(NULL, 10);
    sls_remove(lst, -100);
    sls_remove(lst, 2);
    return 0;
}
