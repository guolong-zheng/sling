#include "stdhipmem.h"

struct slave_item * dll_destroy_slave(struct slave_item * dll)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  struct slave_item * d = dll;
  struct slave_item * next = NULL;
  while(d != NULL)
   /*@
  infer[@shape]
  requires true
  ensures true;
*/
   {
     //loop
    next = d->next;
    free(d);
    d = next;
  }
  //post
  return dll;
}
