#include "stdhipmem.h"


MemReg * split_memory_region(MemReg * curr, int offset)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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
