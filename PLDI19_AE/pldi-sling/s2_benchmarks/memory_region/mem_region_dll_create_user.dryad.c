#include "stdhipmem.h"



MemReg * memory_region_create_user_space_region()
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  MemReg * r  = memory_region_init(NULL, 0, 0, 0, 1);
  MemReg * r1 = memory_region_init(NULL, 0, 0, 786432, 65536);
  r->next = r1;
  r1->prev = r;
  return r;
}
