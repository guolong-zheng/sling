#include "sls.h"
#include <stdlib.h>

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
    Node * res = sls_remove(lst, rand());
    return 0;
}
