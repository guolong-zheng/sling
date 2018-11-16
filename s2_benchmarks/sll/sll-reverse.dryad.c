#include "stdhipmem.h"

SNnode * sll_reverse(SNnode * x)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
	SNnode * y = NULL;
        SNnode * tmp = NULL;
	while (x != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		tmp = x->next;
		x->next = y;
		y = x;
		x = tmp;
	}
	return y;
}
