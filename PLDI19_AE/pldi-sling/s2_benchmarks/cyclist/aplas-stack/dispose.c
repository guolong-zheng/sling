#include "stdhipmem.h"


void dispose(struct stack* s)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  struct node* n = s->head;
  while(n != NULL)
  {
    struct node* tmp = n;
    n = n->next;
    free(tmp);
  }
  free(s);
}
