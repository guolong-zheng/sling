#include "stdhipmem.h"


struct stack* create_stack()
/*@
   infer[@shape]
   requires true
   ensures true;
*/
{
  //pre
  struct stack* s = malloc(sizeof(struct stack));
  s->head = NULL;
  //post
  return s;
}
