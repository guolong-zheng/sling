#include "stdhipmem.h"

struct slave_item * dll_insert_slave(struct slave_item * x)
/*@
   infer[@shape]
   requires true
   ensures true;
*/
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
