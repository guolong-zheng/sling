#include "dl.h"
#include <stdlib.h>

DLNode * dl_remove(DLNode * lst)
{
  //pre
  if (lst == NULL) {
      //post
    return NULL;
  } else {
    int nondet;
    DLNode * curr = lst;
    while(nondet && curr->next != NULL)
    {
      //loop
      nondet = rand_num();
      curr = curr->next;
    }
    DLNode * tmp = curr->next;
    if (tmp != NULL) {
      DLNode * tmp_next = tmp->next;
      curr->next = tmp_next;
      if(tmp_next != NULL){
        tmp_next->prev = curr;
      }
      free(tmp);
    }
    //post
    return lst;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    DLNode * res = dl_remove(lst);
    return 0;
}
