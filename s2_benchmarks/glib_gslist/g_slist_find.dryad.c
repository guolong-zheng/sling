#include "stdhipmem.h"



Node * g_slist_find(Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	while(list != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		if (list->key == data) {
			break;
		}
		list = list->next;
	}
	return list;
}

