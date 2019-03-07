#include "stdhipmem.h"




Node * create(int sz)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * h = NULL;

  while(sz > 0) 
  /*@
 infer[@shape]
 requires true
 ensures true;
 */
  {
    sz --;
    Node * e = (Node *)malloc(sizeof(Node));

    e->next = h;
    h = e;
  }
  return h;
}
