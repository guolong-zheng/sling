#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void dll_destroy_slave(struct slave_item * dll)
  /*D_requires dll^(dll) */
  /*D_ensures  emp */
{
  //pre
  struct slave_item * d = dll;
  struct slave_item * next = NULL;
  while(d != NULL)
    /*D_invariant dll^(d) */
   {
     //loop
    next = d->next;
    free(d);
    d = next;
  }
  //post
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    
}
