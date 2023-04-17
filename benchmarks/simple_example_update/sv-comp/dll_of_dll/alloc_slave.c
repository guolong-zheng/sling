#include "header.h"
#include <stdio.h>
#include <stdlib.h>

struct slave_item * alloc_or_die_slave(void)
  /*D_ensures (dll^(ret) & ((ret |-> loc next: nil; loc prev: nil) * true)) */
{
  //pre
  struct slave_item * ptr = (struct slave_item *) malloc(sizeof(struct slave_item));
  ptr->next = NULL;
  ptr->prev = NULL;
  //post
  return ptr;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    alloc_or_die_slave();
}
