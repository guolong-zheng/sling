#include "stdhipmem.h"



int g_slist_nth_data(Node * list, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	int res;
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
	if (list != NULL) {
		res = list->key;
	} else {
		res = -1;
	}
	return res;
}
