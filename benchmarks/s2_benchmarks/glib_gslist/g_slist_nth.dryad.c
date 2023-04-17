#include "stdhipmem.h"



Node * g_slist_nth(Node * list, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	while(n > 0 && list != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		n--;
		list = list->next; 
	}
	return list;
}

