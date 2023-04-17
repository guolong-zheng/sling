#include "stdhipmem.h"


int llist_removeFirst(struct llist *l)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{

  struct node *nf = l->first;
  struct node *nfn = nf->next;
  int nfv = nf->value;
  free(nf);
  l->first = nfn;

  return nfv;
}


