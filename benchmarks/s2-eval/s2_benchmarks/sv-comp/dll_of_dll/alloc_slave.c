#include "stdhipmem.h"

struct slave_item * alloc_or_die_slave(void)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  struct slave_item * ptr = (struct slave_item *) malloc(sizeof(struct slave_item));
  ptr->next = NULL;
  ptr->prev = NULL;

  return ptr;
}
