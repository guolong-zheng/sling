#include <stdlib.h>
#include <stdio.h>

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

MemReg * memory_region_create_user_space_region()
{
  MemReg * r  = memory_region_init(NULL, 0, 0, 0, 1);
  MemReg * r1 = memory_region_init(NULL, 0, 0, 786432, 65536);
  r->next = r1;
  r1->prev = r;
  return r;
}

MemReg * split_memory_region(MemReg * curr, int offset)
{
  if (offset >= curr->size) {
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
  return next;
}
