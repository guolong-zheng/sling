#include "header.h"
#include <stdlib.h>
#include <stdio.h>

MemReg * split_memory_region(MemReg * curr, int offset)
{
  //pre
  if (offset >= curr->size) {
    //post
    return NULL;
  }

  MemReg * old_next = curr->next;
  MemReg * next = NULL;
  if (offset > curr->file_size) {
    next = memory_region_init(NULL, 0, 0, curr->start_address + offset, curr->size - offset);
  } else {
    next = memory_region_init(curr->file, 0, 0, curr->start_address + offset, curr->size - offset);
    curr->file_size = offset;
  }

  curr->size = offset;
  next->prev = curr;
  next->next = old_next;

  if(old_next != NULL) {
    old_next->prev = next;
  }
  curr->next = next;
  //post
  return next;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    
}
