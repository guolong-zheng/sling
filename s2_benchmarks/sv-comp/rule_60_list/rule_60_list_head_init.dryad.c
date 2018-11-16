#include "stdhipmem.h"


struct list_head * list_head_init(void)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  struct list_head * head = (struct list_head *) malloc(sizeof(*head));
  head->prev = NULL;
  head->next = NULL;
  head->inserted = 1;
  return head;
}

