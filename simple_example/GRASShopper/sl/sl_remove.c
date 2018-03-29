#include "header.h"
#include <stdlib.h>

Node * sl_remove(Node * lst)
{
  //pre
  if (lst == NULL) {
    //post
    return NULL;
  } else {
    int nondet = rand();
    Node * curr = lst;
    while(nondet && curr->next != NULL)
    {
      //loop
      nondet = rand();
      curr = curr->next;
    }
    Node * tmp = curr->next;
    if (tmp != NULL) {
      Node * tmp_next = tmp->next;
      curr->next = tmp_next;
      free(tmp);
    }
    //post
    return lst;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res = sl_remove(lst);
    return 0;
}
