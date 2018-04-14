#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct slave_item * dll_insert_slave(struct slave_item * x)
{
  //pre
  struct slave_item * item = (struct slave_item *) malloc(sizeof(struct slave_item));
  item->next = NULL;
  item->prev = NULL;

  struct slave_item * next = x;
  item->next = next;
  if (next != NULL) {
    next->prev = item;
  }
  //post
  return item;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    struct slave_item * x = create_dll(size);
    dll_insert_slave(x);
    return 0;
}
