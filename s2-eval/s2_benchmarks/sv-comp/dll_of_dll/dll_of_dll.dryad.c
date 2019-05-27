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

struct slave_item * dll_insert_slave(struct slave_item * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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


struct slave_item * dll_create_slave(int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  struct slave_item * dll = NULL;
  dll = dll_insert_slave(dll);
  dll = dll_insert_slave(dll);
  while(n > 0) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    dll = dll_insert_slave(dll);
  }
  return dll;
}

void dll_destroy_slave(struct slave_item * dll)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  struct slave_item * d = dll;
  while(d != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
   {
    struct slave_item * next = d->next;
    free(d);
    d = next;
  }
}
