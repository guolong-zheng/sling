#include "stdhipmem.h"



SNnode * find_last_sorted(SNnode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
      /*@
       infer[@shape]
       requires true
       ensures true;
       */
		{ 
			curr = curr->next;
		}
	}
	return curr;
}
