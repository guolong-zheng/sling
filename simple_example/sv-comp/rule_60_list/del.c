#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void * list_del(struct list_head * entry)
{
  //pre
  struct list_head * prev = entry->prev;
  struct list_head * next = entry->next;
  if (prev != NULL) {
    prev->next = next;
  }
  if (next != NULL) {
    next->prev = prev;
  }
  entry->next = NULL;
  entry->prev = NULL;
  free(entry);
  //post
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * hd = create_list(size);
    list_del(hd);
    return 0;
}
