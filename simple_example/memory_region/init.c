#include "header.c"
#include <stdio.h>
#include <stdlib.h>

MemReg * memory_region_init(BackingFile * file_,
                            int file_offset_,
                            int file_size_,
                            int start_address_,
                            int size_)
{
  MemReg * mr = (MemReg *) malloc(sizeof(MemReg));
  mr->file = file_;
  mr->file_offset = file_offset_;
  mr->file_size = file_size_;
  mr->start_address = start_address_;
  mr->size = size_;
  mr->prev = NULL;
  mr->next = NULL;
  return mr;
}
