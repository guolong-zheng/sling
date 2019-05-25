#include "stdhipmem.h"

struct slave_item * dll_create_slave(int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  struct slave_item * dll = NULL;
  while(n > 0)
    /*@
 infer[@shape]
 requires true
 ensures true;
 */
  {
    n--;
    dll = insert_slave(dll);
  }
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
