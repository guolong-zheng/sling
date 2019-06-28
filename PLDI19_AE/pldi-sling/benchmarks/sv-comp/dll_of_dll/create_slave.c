#include "header.h"
#include <stdio.h>
#include <stdlib.h>

struct slave_item * insert_slave(struct slave_item * x);
struct slave_item * dll_create_slave(int n);

struct slave_item * dll_create_slave(int n)
{
  //pre
  struct slave_item * dll = NULL;
  //dll = dll_insert_slave(dll);
  //dll = dll_insert_slave(dll);
  while(n > 0)
  {
    //loop
    n--;
    dll = insert_slave(dll);
  }
  //post
  return dll;
}

struct slave_item * insert_slave(struct slave_item * x)
{
  struct slave_item * item = (struct slave_item *) malloc(sizeof(struct slave_item));

  item->next = NULL;
  item->prev = NULL;

  struct slave_item * next = x;
  item->next = next;
  if (next != NULL) {
    next->prev = item;
  }
  return item;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    dll_create_slave(size);
    return 0;
}
