#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sls_filter(Node * x)
{
  //pre
  Node * prv = NULL;
  Node * curr = x;
  Node * res = x;
  Node * old_curr = NULL;
  Node * old_curr_next = NULL;
  int nondet = 0;
  while(curr != NULL)
  {
    //loop
    old_curr = curr;
    curr = curr->next;
    nondet = rand() % 3 - 1;
    if(nondet > 0) {
      if (prv != NULL) {
        old_curr_next = old_curr->next;
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
    Node * lst = create_list(1, size);
    Node * res = sls_filter(lst);
    sls_filter(NULL);
    return 0;
}
