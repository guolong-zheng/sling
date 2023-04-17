#include "stdhipmem.h"

void iter_dispose(struct iter *i)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
    //pre
    freei(i);
    //post
}

