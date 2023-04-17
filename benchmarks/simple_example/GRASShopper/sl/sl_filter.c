#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sl_filter(Node * x)
{
  //pre
  Node * prv = NULL;
  Node * curr = x;
  Node * res = x;
  while(curr != NULL)
  {
    //loop
    Node * old_curr = curr;
    curr = curr->next;
     int nondet = rand();
    if(nondet) {
      if (prv != NULL) {
        Node * old_curr_next = old_curr->next;
        prv->next = old_curr_next;
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
    Node * lst = create_list(size);
    Node * res = sl_filter(lst);
    return 0;
}
