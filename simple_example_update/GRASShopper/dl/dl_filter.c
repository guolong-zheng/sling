#include "header.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * dl_filter(DLNode * x)
{
  //pre
  DLNode * prv = NULL;
  DLNode * curr = x;
  DLNode * res = x;
  DLNode * old_curr = NULL;
  DLNode * old_curr_next = NULL;
  while(curr != NULL)
  {
      //loop
    old_curr = curr;
    curr = curr->next;
    int nondet = rand();
    if(nondet) {
      if (prv != NULL) {
        old_curr_next = old_curr->next;
        prv->next = old_curr_next;
        if (old_curr_next != NULL) {
          old_curr_next->prev = prv;
        }
      } else {
        res = old_curr->next;
      }
      free(old_curr);
    } else {
      prv = old_curr;
    }
  }
  //post
  return res;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    DLNode * res = dl_filter(lst);
    dl_filter(NULL);
    return 0;
}
