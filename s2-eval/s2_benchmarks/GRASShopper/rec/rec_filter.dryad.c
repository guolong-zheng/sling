#include "stdhipmem.h"



Node * rec_filter(Node * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  Node * n1;
  Node * n2;
  int nondet;
  if (x == NULL) { 
    return x;
  } else if (nondet) { 
    n1 = x->next;
    n2 = rec_filter(n1);
    x->next = n2;
    return x;
  } else {
    n1 = x->next;
    free(x);
    n2 = rec_filter(n1);
    return n2;
  }
}
